from flask import Flask, render_template, session, make_response

app = Flask(__name__)
app.secret_key = "abc123"
flag = flag = open("flag.txt", "r").read()

@app.route('/', methods=["GET"])
def index():
    admin = session.get("admin")
    if admin:
        return make_response(render_template('index.html', flag=flag))
    else:
        session.clear()
        session["admin"] = False
        return make_response(render_template('index.html', flag="XXXXXXXXXX"))

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)
