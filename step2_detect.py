import json
from graphify.detect import detect
from pathlib import Path
result = detect(Path('c:/Users/fuzzy/Downloads/GTProxy-3.0/GTProxy-3.0'))
Path('graphify-out/.graphify_detect.json').write_text(json.dumps(result, ensure_ascii=False), encoding='utf-8')
