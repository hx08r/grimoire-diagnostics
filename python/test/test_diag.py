import grimoire_diag
import time

meta = grimoire_diag.Metadata()
meta.file = "test_diag.py"
meta.line = 123
meta.function = "demo_func"
meta.tags = ["py", "test"]
meta.correlationId = "py456"
meta.set_timestamp(int(time.time() * 1000))

diag = grimoire_diag.Diagnostics()
diag.add_metadata(meta)

exporter = grimoire_diag.FileExporter("py_test.log", False)
diag.add_exporter(exporter)

diag.report_warning("Python warning works!")
diag.report_error("Python error works!")

print("Done. Check py_test.log")
