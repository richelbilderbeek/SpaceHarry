#!/usr/bin/env python3
"""Play the WebAssembly game on the 'Play' page of a built website.

Usage: test_play_page.py <URL of the play page>

Checks that the menu shows up, that clicking 'Start Game' starts
the game and that the game keeps running while playing it.
The menu and game are found by their blue sky,
as fonts differ between a desktop and a browser.
"""
import io
import sys
import time

from PIL import Image, ImageChops, ImageStat
from playwright.sync_api import sync_playwright

SKY = (0, 0, 255)
MENU_SIZE = (501, 502)  # See spaceharrymenudialog.cpp
START_GAME = (304, 141)  # Center of 'Start Game', relative to the menu
START_TIMEOUT_SECS = 120
GAME_TIMEOUT_SECS = 30


def sky_box(shot):
    """The bounding box of all pixels that have the color of the sky."""
    mask = Image.eval(
        ImageChops.difference(shot, Image.new("RGB", shot.size, SKY))
        .convert("L"),
        lambda value: 255 if value == 0 else 0)
    return mask.getbbox()


def is_soil(pixel):
    """Is this pixel one of the two greens of the soil?"""
    return pixel in [(0, 255, 0), (0, 128, 0)]


def main():
    url = sys.argv[1]
    errors = []
    with sync_playwright() as playwright:
        browser = playwright.chromium.launch()
        page = browser.new_page(viewport={"width": 1280, "height": 1100})
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.on("console", lambda m: print(f"console: {m.text}"))
        page.goto(url)
        frame = page.locator("iframe")

        def screenshot():
            data = frame.screenshot()
            return Image.open(io.BytesIO(data)).convert("RGB")

        print("Waiting for the menu to show up")
        deadline = time.time() + START_TIMEOUT_SECS
        box = None
        while time.time() < deadline:
            box = sky_box(screenshot())
            print(f"Sky found at: {box}")
            if box and abs(box[2] - box[0] - MENU_SIZE[0]) <= 2:
                break
            time.sleep(1)
        assert box, "No menu shown"
        width = box[2] - box[0]
        assert abs(width - MENU_SIZE[0]) <= 2, f"Menu has width {width}"
        assert not errors, errors

        print("Clicking 'Start Game'")
        frame.click(position={"x": box[0] + START_GAME[0],
                              "y": box[1] + START_GAME[1]})

        print("Waiting for the game to fill the page")
        deadline = time.time() + GAME_TIMEOUT_SECS
        shot = screenshot()
        while time.time() < deadline:
            shot = screenshot()
            box = sky_box(shot)
            print(f"Sky found at: {box}")
            if box and box[0] <= 2 and box[2] - box[0] > MENU_SIZE[0] + 100:
                break
            time.sleep(1)
        assert box and box[2] - box[0] > MENU_SIZE[0] + 100, "No game shown"
        width, height = shot.size
        assert is_soil(shot.getpixel((5, height * 3 // 4))), "No soil"
        assert not errors, errors

        print("Playing the game")
        shots = []
        for key in ["ArrowLeft", "ArrowUp", "Space", "ArrowRight", "Space"]:
            page.keyboard.down(key)
            time.sleep(0.3)
            page.keyboard.up(key)
            shots.append(screenshot())
        differences = [
            sum(ImageStat.Stat(ImageChops.difference(a, b)).mean)
            for a, b in zip(shots, shots[1:])
        ]
        print(f"Differences between screenshots: {differences}")
        assert all(d > 0 for d in differences), "The game does not move"
        assert sky_box(shots[-1]), "The game is gone"
        assert not errors, errors
        browser.close()
    print("OK: the game can be played")


if __name__ == "__main__":
    main()
