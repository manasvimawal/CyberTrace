from flask import Flask, jsonify, render_template
import subprocess
import json

app = Flask(__name__)

@app.route("/")
def dashboard():
    return render_template("index.html")

@app.route("/api/logs")
def get_logs():
    try:
        result = subprocess.run(
            ["./gui_bridge"],
            capture_output=True,
            text=True,
            check=True
        )

        data = json.loads(result.stdout)
        return jsonify(data)

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run(debug=True)