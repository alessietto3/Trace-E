Import("env")

import re
from pathlib import Path


secret_header = Path(env.subst("$PROJECT_DIR")) / "src" / "secret.h"
secret_text = secret_header.read_text(encoding="utf-8")
match = re.search(
    r'^\s*#define\s+OTA_PASSWORD\s+"([^"\r\n]+)"\s*$',
    secret_text,
    re.MULTILINE,
)

if match is None:
    raise RuntimeError(f"OTA_PASSWORD string definition not found in {secret_header}")

env.Replace(UPLOAD_FLAGS=[f"--auth={match.group(1)}"])