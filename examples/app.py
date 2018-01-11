import SimpleHTTPServer
import SocketServer
import logging
import sys

#PORT = 12345
# PORT = 8080
PORT = int(sys.argv[1])

class GetHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):

    def do_GET(self):
        logging.error(self.headers)
        SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)


Handler = GetHandler
httpd = SocketServer.TCPServer(("", PORT), Handler)

httpd.serve_forever()

