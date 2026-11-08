import json
from pathlib import Path

root = Path(__file__).parent / 'ConfigInicial' / 'Models'
report = {}
for file in sorted(root.glob('*.obj')):
    lo = [float('inf')] * 3
    hi = [float('-inf')] * 3
    count = 0
    for line in file.read_text(encoding='utf-8', errors='replace').splitlines():
        if line.startswith('v '):
            v = list(map(float, line.split()[1:4]))
            lo = [min(a, b) for a, b in zip(lo, v)]
            hi = [max(a, b) for a, b in zip(hi, v)]
            count += 1
    report[file.name] = dict(min=lo, max=hi, size=[b-a for a,b in zip(lo,hi)], vertices=count)
Path(__file__).with_name('dimensiones-modelos.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
for name, value in report.items():
    print(name, 'min=', [round(v, 4) for v in value['min']], 'max=', [round(v, 4) for v in value['max']], 'size=', [round(v,4) for v in value['size']])
