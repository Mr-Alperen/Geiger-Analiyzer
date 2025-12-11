from flask import Flask, render_template
import pandas as pd

app = Flask(__name__)

@app.route('/')
def index():
    data = pd.read_csv('log/geiger_log.txt', sep='|', header=None, names=['Time','JSON'])
    return render_template('plot.html', data=data.to_html())

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)