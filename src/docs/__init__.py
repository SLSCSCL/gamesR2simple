from webbrowser import open_new_tab as open_docs

class NotInstalledError(ModuleNotFoundError):
    pass

try:
    from importlib.resources import files #Python 3.9+
except ModuleNotFoundError:
    try:
        from importlib_resources import files #Python 3.7 - 8
    except ModuleNotFoundError:
        raise NotInstalledError(
            "You need to install importlib_resources on Python 3.8 and less."
        ) from None

file_path = files("gamesR2simple.docs") / "docs.html"

if not open_docs(file_path.as_uri()):
    print("An error occured when trying to open the docs.",
        "But, you can find them here:\n" + file_path)
