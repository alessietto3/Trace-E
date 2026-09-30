import os
import re
from pathlib import Path

def extract_faces():
    src_dir = Path(__file__).resolve().parent.parent / "src"
    h_file = src_dir / "face-bitmaps-tft.h"
    out_dir = Path(__file__).resolve().parent.parent / "sdcard_faces" / "faces"
    out_dir.mkdir(parents=True, exist_ok=True)

    if not h_file.exists():
        print(f"Error: {h_file} not found!")
        return

    print(f"Reading {h_file}...")
    content = h_file.read_text(encoding="utf-8")

    # Match all const unsigned char epd_bitmap_<name> [] PROGMEM = { ... };
    pattern = r'const\s+unsigned\s+char\s+epd_bitmap_([a-zA-Z0-9_]+)\s*\[\]\s*PROGMEM\s*=\s*\{([^}]+)\};'
    matches = re.findall(pattern, content)

    print(f"Found {len(matches)} bitmaps.")

    exported = 0
    for name, hex_body in matches:
        hex_tokens = [tok.strip() for tok in hex_body.split(',') if tok.strip()]
        byte_vals = bytearray()
        for tok in hex_tokens:
            try:
                byte_vals.append(int(tok, 16))
            except ValueError:
                pass

        if len(byte_vals) != 2560:
            print(f"Warning: {name} size is {len(byte_vals)} bytes (expected 2560)")

        # Naming convention:
        # If name is "idle", filename is "idle_0.bin"
        # If name is "idle_blink_1", filename is "idle_blink_1.bin"
        # If name has no trailing _<num>, treat as _0.bin
        parts = name.rsplit('_', 1)
        if len(parts) == 2 and parts[1].isdigit():
            clean_name = f"{parts[0]}_{parts[1]}.bin"
        else:
            clean_name = f"{name}_0.bin"

        out_path = out_dir / clean_name
        out_path.write_bytes(byte_vals)
        exported += 1

    print(f"Successfully exported {exported} face frames to: {out_dir}")

if __name__ == "__main__":
    extract_faces()
