#!/usr/bin/python3
from os.path import join, dirname, realpath
from cgi     import FieldStorage
from sys     import stderr, stdout
from cgitb   import enable

enable()
stderr  = stdout

print("Access-Control-Allow-Origin: *")
print("Content-type: text/html\n\n")

file    = lambda f: join(dirname(realpath(__file__)), f)

msgs0   = open(file('msgs.txt'), 'r')

form    = FieldStorage()
print(msgs0.read())
if form:
    if [int(form[k].value) for k in form if str(k) == "flag"][0]:
        with open(file('msgs.txt'), 'a') as msgs1:
            msgs1.write(form.getfirst("name") + ": " + form.getfirst("message") + " <br/>")
            msgs1.close()
    else:
        with open(file('msgs.txt'), 'w') as msgs1:
            msgs1.write("alice: hello <br/> bob: whatever <br/>")
            msgs1.close()

    redirectURL = "../p3.html"
    print('<html>')
    print('  <head>')
    print('    <meta http-equiv="refresh" content="0;url='+str(redirectURL)+'" />')
    print('  </head>')
    print('</html>')

msgs0.close()