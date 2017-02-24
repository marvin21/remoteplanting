
import BaseHTTPServer
from SimpleHTTPServer import SimpleHTTPRequestHandler
import SocketServer
import json as simplejson
import random
from urlparse import parse_qs
import serial


class Server (SimpleHTTPRequestHandler):    

    
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def not_authorized(self):
        self.send_response(401)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def not_found(self):
        self.send_response(404)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def do_GET(self):

        print 'Anfrage : '+ self.path

        # check authorization
        if (self.headers.getheader('auth-token') is None) or (self.headers.getheader('auth-token') != 'gurke'):
            self.not_authorized()
            return

    def do_HEAD(self):
        print 'header method'
        self._set_headers()

    def do_POST(self):        
        print 'Anfrage: ' + self.path
        print parse_qs(self.path[2:])
        if parse_qs(self.path[2:]) == {}:
            print 'no action found'
            self.not_found()
            return
        
        action = parse_qs(self.path[2:]).get('action')[0]
        print 'recieved action = '+ action
        self._set_headers()
        self.wfile.write("action = " + action)
        content_len = int(self.headers.getheader('content-length'))
        post_body = self.rfile.read(content_len)
        data = simplejson.loads(post_body)       
    
        buf = ''.join(chr(x) for x in [data['X'],data['Y'], data['Z']])

        print "Received Data:" + "\tX:" +  str(data['X']) + "\tY:" + str(data['Y']) + "\tZ:" + str(data['Z'])
        print "Transoformed Data:"+ "\tX:" + buf[0]  + "\tY:" + buf[1] + "\tZ:" + buf[2]
        
        #show buffer if necessary.
        #print buf[0]
        #print buf[1]
        #print buf[2]

        #move robot        
        ser.write(buf);                                                                                                                                                                                                                                                             

def run(server_class=BaseHTTPServer.HTTPServer, handler_class=Server, port=80):
    server_address = ('', port)        
    httpd = server_class(server_address, handler_class)
    global ser
    ser = serial.Serial('/dev/ttyACM1', 115200)
    print 'Starting httpd on port 80...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

if len(argv) == 2:
    run(port=int(argv[1]))
else:
    run()
