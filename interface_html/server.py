import http.server
import os
import subprocess
from urllib.parse import urlparse, parse_qs

class CustomHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):

        if self.path == '/' or self.path == '/index.html':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            
            with open('templates/visual_http.html', 'r') as f:
                self.wfile.write(f.read().encode())
            return

        if self.path.startswith('/style.css'):
            self.send_response(200)
            self.send_header('Content-type', 'text/css')
            self.end_headers()
            
            with open('templates/style.css', 'r') as f:
                self.wfile.write(f.read().encode())
            return
        

        self.send_response(404)
        self.end_headers()
        self.wfile.write(b'Not found')

    def do_POST(self):

        if self.path == '/process':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            

            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            

            response = "<html><body>"
            response += "<h2>Operation Result:</h2>"
            response += "<pre>Processing your request...</pre>"
            response += "<p>This is a placeholder for the actual result.</p>"
            response += "<p>In a real implementation, this would show the result of your operation.</p>"
            response += "<a href='/'>Back to main</a>"
            response += "</body></html>"
            
            self.wfile.write(response.encode())
            return
        
        self.send_response(404)
        self.end_headers()
        self.wfile.write(b'Not found')


def run_server():
    server_address = ('', 8000)
    httpd = http.server.HTTPServer(server_address, CustomHandler)
    print('Server running on http://localhost:8000/')
    httpd.serve_forever()

if __name__ == '__main__':
    run_server()