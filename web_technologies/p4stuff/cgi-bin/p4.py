#!/usr/bin/python
import cgi, os
import cgitb; cgitb.enable()

form     = cgi.FieldStorage()
data = form['file']

if data.filename:
    file_to_save = os.path.basename(data.filename)
    open('./uploads/' + file_to_save, 'wb').write(data.file.read())

print("Access-Control-Allow-Origin: *")
print("Content-type: text/html\n\n")
redirectURL = "../p4.html"
print('<html>')
print('  <head>')
print('    <meta http-equiv="refresh" content="0;url='+str(redirectURL)+'" />')
print('  </head>')
print('</html>')