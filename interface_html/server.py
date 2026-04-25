from flask import Flask, request
from logic import calculate_sum
import os

app = Flask(__name__, static_folder='photo', static_url_path='/photo')

try:
    with open('visual_http.html', 'r', encoding='utf-8') as f:
        HTML_TEMPLATE = f.read()
except FileNotFoundError:
    HTML_TEMPLATE = "<h1>Ошибка: файл visual_http.html не найден</h1>"

@app.route('/', methods=['GET', 'POST'])
def index():
    result = ''
    if request.method == 'POST':
        try:
            a = int(request.form['a'])
            b = int(request.form['b'])
            result = str(calculate_sum(a, b))
        except:
            result = "Ошибка ввода"

    return HTML_TEMPLATE.replace('{{ result }}', result)


# 👇 ВАЖНО для интернета
if __name__ == '__main__':
    port = int(os.environ.get("PORT", 8080))
    app.run(host='0.0.0.0', port=port)