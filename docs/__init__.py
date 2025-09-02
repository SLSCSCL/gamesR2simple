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
    print("An error occured when trying to use the webbrowser module to open",
          "the docs. ")

##from logging import getLogger
##from sys import exit as kill
##from threading import Thread
##from time import sleep
##from urllib.request import urlopen as open_url
##from urllib.error import URLError
##from webbrowser import open_new_tab as _open
##
##from flask import Flask, render_template as render, jsonify, request
##from jinja2.exceptions import TemplateNotFound
##
##app = Flask(__name__)
##
##with open("./loc.txt", "w") as f:
##    print("Hello, I am Baymax.", file=f)
##
### these are used once all bugs are worked out, so that the logs 
### don't spam the console (if there is one being used)
###app.logger.disabled = True
###getLogger('werkzeug').disabled = True
##
##@app.route("/")
##def index():
##    """Home page of the documentation."""
##    return render("index.html",)
##
##def try_to_get_template(name):
##    """We need to make sure that a given class or module exists."""
##    try:
##        return render(name)
##    except TemplateNotFound:
##        return render("not_found.html", error=name)
##
##@app.route("/classes/<cls>")
##def get_class_docs(cls):
##    return try_to_get_template(f"classes/{cls}")
##
##@app.route("/modules/<module>")
##def get_module_docs(module):
##    return try_to_get_template(f"modules/{module}")
##
##@app.errorhandler(404)
##def not_found(e):
##    return render("404.html"), 404
##
##still_open = True
##seconds_left, _30_MIN = 0, 15#30 * 60
##
##@app.route("/get_time_left")
##def get_time_left():
##    global seconds_left
##    
##    return jsonify({"time": seconds_left})
##
##@app.route("/reset_time_left")
##def reset_time():
##    global still_open
##    
##    still_open = True
##
##    # we must return something, otherwise Flask will return an 
##    # 'Internal Server Error' (500) response
##    return ""
##
##@app.route("/shutdown", methods=["POST"])
##def shutdown():
##    func = request.environ.get('werkzeug.server.shutdown')
##    if func is None:
##        raise RuntimeError('Not running with the Werkzeug Server')
##    func()
##    return "Shutdown successful"
##
##SHUTDOWN_JS = \
##"""
##<script>
##document.addEventListener("DOMContentLoaded", async function() {
##    const shutdown = await fetch("/shutdown");
##});
##</script>
##"""
##
##@app.route("/_js_shutdown")
##def js_shutdown():
##    return SHUTDOWN_JS
##
##def open_docs(url):
##    global still_open, seconds_left, _30_MIN
##    
##    while True:
##        try: # see if Flask has built the web-app yet
##            with open_url(url) as r:
##                if r.status == 200:
##                    break
##        except URLError:
##            # Flask has not built the web-app - try again after 0.5 seconds
##            sleep(0.5)
##
##    _open(url) # now we can finally open up the web-app
##
##    # We don't want the web-app the run forever in the background, so we will 
##    # close it after 30 minutes. If the web-app is be opened by a .pyw file, 
##    # it is impossible to use Ctrl-C to stop it, so we will use a timer to 
##    # close it after 30 minutes. In the JS for the web-app, we will reset the timer
##    # according to the user's input by using the previously defined function 
##    # 'reset_timer', so that the  web-app will not close if the user is still using it.
##    while still_open:
##        still_open = False
##        seconds_left = _30_MIN
##        for _ in range(_30_MIN, 0, -1):
##            seconds_left -= 1
##            sleep(1)
##
##    # end the program so that it doesn't run forever in the background
##    try:
##        open_url(url + "/_js_shutdown")
##    except Exception:
##        pass
##
### opening the documents must be done in a thread, 
### because app.run() will block the main thread
##Thread(target=open_docs, args=("http://localhost:5000",)).start()
##app.run(use_reloader=False)
