"""
Helper tool to convert any PNG, JPG, BMP image into a 160x128 .bin file
ready to be copied to the SD card (/faces/<name>_<frame>.bin) or uploaded via Web UI.
"""

import sys
from pathlib import Path

def convert_image(input_path, output_path=None, threshold=128, invert=False):
    try:
        from PIL import Image
    except ImportError:
        print("Pillow library not installed. Install it with: pip install pillow")
        return

    in_path = Path(input_path)
    if not in_path.exists():
        print(f"Error: {in_path} does not exist.")
        return

    if output_path is None:
        output_path = in_path.with_suffix(".bin")
    else:
        output_path = Path(output_path)

    img = Image.open(in_path).convert("L")  # Grayscale
    img = img.resize((160, 128), Image.Resampling.LANCZOS)

    # Convert to 1-bit monochrome bitmap
    # Each byte = 8 horizontal pixels (MSB first)
    byte_arr = bytearray()
    pixels = img.load()

    for y in range(128):
        for byte_x in range(20): # 160 / 8 = 20 bytes per row
            b = 0
            for bit in range(8):
                x = byte_x * 8 + bit
                val = pixels[x, y]
                is_on = (val > threshold)
                if invert:
                    is_on = not is_on
                if is_on:
                    b |= (1 << (7 - bit))
            byte_arr.append(b)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(byte_arr)
    print(f"Converted {in_path.name} -> {output_path} ({len(byte_arr)} bytes)")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python image_to_face_bin.py <input_image.png> [output_file.bin]")
    else:
        out = sys.argv[2] if len(sys.argv) > 2 else None
        convert_image(sys.argv[1], out)
