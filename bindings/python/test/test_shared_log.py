import grimoire_diag
import subprocess
import json
import os
import time
import sys

def test_shared_log_integration():
    # Find the absolute repo root
    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.."))

    # Correct path to the binary in build/core
    exe_name = os.path.join(repo_root, "build/core/grimoire_demo")
    if sys.platform == "win32":
        exe_name += ".exe"

    print(f"Running executable: {exe_name}")
    assert os.path.exists(exe_name), f"Executable not found: {exe_name}"
    subprocess.run([exe_name], check=True)

    # Run Python diagnostics
    meta = grimoire_diag.Metadata()
    meta.file = "test_shared_log.py"
    meta.line = 99
    meta.function = "shared_log_test"
    meta.tags = ["py", "integration"]
    meta.correlationId = "py_shared"
    meta.set_timestamp(int(time.time() * 1000))

    diag = grimoire_diag.Diagnostics()
    diag.add_metadata(meta)

    exporter = grimoire_diag.FileExporter("shared_diag.log", True)  # append
    diag.add_exporter(exporter)

    diag.report_warning("Python integration warning")
    diag.report_error("Python integration error")

    # Validate the log
    with open("shared_diag.log") as f:
        lines = [json.loads(line) for line in f]

    messages = [line["message"] for line in lines]
    assert any("C++ warning" in m or "C++ error" in m for m in messages)
    assert any("Python integration warning" in m for m in messages)
    assert any("Python integration error" in m for m in messages)

    print("Shared log test passed — C++ and Python wrote to the same file!")
