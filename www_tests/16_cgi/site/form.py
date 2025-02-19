#!/usr/bin/env python3

import cgi
import html
import os
from http import cookies

# Function to retrieve cookie values
def get_cookie(cookie_name, default=''):
    cookie_obj = cookies.SimpleCookie(os.environ.get('HTTP_COOKIE', ''))
    if cookie_name in cookie_obj:
        return cookie_obj[cookie_name].value
    return default

# Function to set cookies with a specific name and value
def set_cookie(cookie_name, cookie_value, max_age=2592000):
    print(f"Set-Cookie: {cookie_name}={cookie_value}; Max-Age={max_age}; Path=/")

# Send the Content-Type header first (make sure no body content is printed before this)
print("Content-Type: text/html\n")

# Initialize the form handling
form = cgi.FieldStorage()

# Handle form submission (POST method)
username = form.getvalue('username', '')
email = form.getvalue('email', '')

# If both fields are provided, set cookies and show the entered values
if os.environ['REQUEST_METHOD'] == 'POST' and username and email:
    set_cookie('username', username)
    set_cookie('email', email)
    print(f"Username: {html.escape(username)}<br>\n")
    print(f"Email: {html.escape(email)}<br>\n")

# If the form fields are empty, use cookie values instead
prefill_username = username if username else get_cookie('username', '')  # Use form value, or cookie if empty
prefill_email = email if email else get_cookie('email', '')  # Use form value, or cookie if empty
print("\r\n\r\n")
# HTML form (with cookies to prefill the values if the form fields are empty)
print("""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Form Upload</title>
</head>
<body>
    <h2>Form</h2>
    <form action="/form.py" method="POST" enctype="multipart/form-data">
        <!-- Prefill the form with form values if available, otherwise use cookie values -->
        <input type="text" name="username" value="{0}" />
        <input type="text" name="email" value="{1}" />
        <input type="submit" />
    </form>
</body>
</html>
""".format(
    html.escape(prefill_username),  # Use form value if available, otherwise cookie
    html.escape(prefill_email)      # Use form value if available, otherwise cookie
))
