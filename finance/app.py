import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


def pass_hash(password):
    hash_pass = generate_password_hash(password)
    return str(hash_pass)


def pass_check(password, hashword):
    result = check_password_hash(hashword, password)
    return (result)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get user id from session
    user = session.get('user_id')
    # look up sql database - where user_id = session user. Find quantities of stocks owned. Group By looks by dinstinct values in a certain column
    user_stocks = db.execute("SELECT stock, SUM(stock_quantity) FROM (SELECT * FROM transactions WHERE user_id =?) GROUP BY stock;", user)
    # create a variable where we can calculate total value of holdings
    total_holdings = 0
    # loop over each dict in the list returned from sql. Then we can work out and then out more key value pairs to each stock listing. To pass thru to html
    for i in range(len(user_stocks)):
        stock = user_stocks[i]['stock']
        # look up stock price and add to the specific dict in our user_stocks list
        stock_lookup = lookup(stock)
        price = stock_lookup['price']
        user_stocks[i]['price'] = price
        # extract company name for the stock too
        user_stocks[i]['name'] = stock_lookup['name']
        # work out value of that holding
        stock_quantity = user_stocks[i]['SUM(stock_quantity)']
        value_holding = round(price * stock_quantity, 2)
        user_stocks[i]['value_holding'] = value_holding
        print(user_stocks[i])
        # im adding quantity to the dict in place of SUM(stock_quanity) as Jinja doesnt seem to like that
        user_stocks[i]['quantity'] = stock_quantity
        # add the holding value to total_holdings
        total_holdings += value_holding
    # Now i'm going to loop over my list of holdings - and if any stock quantities are < 1, i'll remove that dict
    for i in range(len(user_stocks)):
        if user_stocks[i]['SUM(stock_quantity)'] < 1:
            del user_stocks[i]
    # next extract users cash from the users table in SQL
    extract_cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
    cash = extract_cash[0]['cash']
    cash = round(cash, 2)
    total_value = round(cash + total_holdings, 2)
    # renderindex template and pass in user_stocks list + cash of user and total holdings value
    return render_template("index.html", user_stocks=user_stocks, cash=cash, total_value=total_value)


@app.route("/account_settings", methods=["GET", "POST"])
@login_required
def account_settings():
    user = session.get('user_id')
    if request.method == "POST":
        # check both current and new pass entered
        if not request.form.get("current_pass"):
            return apology("Please enter a current password", 400)
        if not request.form.get("new_pass"):
            return apology("Please enter a new password", 400)
        # check password confirmation
        if not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("new_pass"):
            return apology("You Password confirmation doesnt match", 400)
        # Ensure current password is correct for current user
        rows = db.execute("SELECT * FROM users WHERE id = ?", user)
        if not check_password_hash(rows[0]["hash"], request.form.get("current_pass")):
            return apology("invalid username and/or password", 400)
        else:
            # hash new password, extracted from form
            hash_new = pass_hash(request.form.get("new_pass"))
            # update password in database
            db.execute("UPDATE users SET hash =? WHERE id=?", hash_new, user)
            flash("Password Updated")
            return render_template("account_settings.html")

    else:
        return render_template("account_settings.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # check stock entered
        if not request.form.get("symbol"):
            return apology("Please enter a stock Symbol", 400)
        # check postive, none fractional shares of stock entered
        shares = request.form.get("shares")
        # check it's not a decimal entry
        if not shares.isdigit():
            return apology("Please enter a whole number of shares", 400)
        # check it's a positive number
        shares = int(shares)
        if shares < 1:
            return apology("Please enter an postive number of shares", 400)
        # look up share cost
        api_response = lookup(request.form.get("symbol"))
        # if no api response, let user know to enter an actual stock
        if not api_response or request.form.get("symbol") == "":
            return apology("Invalid Ticker Symbol entered", 400)
        # work out share cost * quantity required
        price = (api_response.get("price")) * shares
        # check users funds by querying sql db, using id from session
        user_funds = db.execute("SELECT cash FROM users WHERE id = ?", session.get('user_id'))[0]["cash"]
        if user_funds < price:
            return apology("Sorry you don't have enough in your account for that")
        else:
            user = session.get('user_id')
            action = "Buy"
            stock = request.form.get("symbol")
            cost_dollars = price
            timestamp = datetime.datetime.now()
            # insert the stock purchase information into my sql transaction table
            db.execute("INSERT INTO transactions (user_id, stock, action, cost_dollars, timestamp, stock_quantity) VALUES  (?, ?, ?, ?, ?, ?)", user, stock, action, cost_dollars, timestamp, shares)
            # update users funds
            db.execute("UPDATE users SET cash = cash-? WHERE id = ?", cost_dollars, user)
            return index()
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = session.get('user_id')
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user)
    return render_template("history.html",  user_transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return index()

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock_request = request.form.get("symbol")
        api_response = lookup(stock_request)
        if not api_response or stock_request == "":
            return apology("Invalid Ticker Symbol entered", 400)
        print(api_response)
        return render_template("quoted.html", api_response=api_response)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # if request is a post
    if request.method == "POST":
        # ensure a username is entered
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # ensure a password entered
        if not request.form.get("password"):
            return apology("must provide password", 400)
        # check password confirmation
        if not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("password"):
            return apology("You Password confirmation doesnt match", 400)
        # extract username and password from form
        username = request.form.get("username")
        # extract password from form and hash it
        hashword = pass_hash(request.form.get("password"))
        # look at current database, is the username wanted in use?
        current_users = db.execute("SELECT username FROM users")
        for x in current_users:
            xuser = x['username']
            if xuser == username:
                # if so return apology
                return apology("Username already in use!", 400)
        # else add user and hashed password to the database
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, hashword)
        # Query database for user id and add to sessions
        user = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = user[0]['id']
        # Redirect user to home page
        return index()
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = session.get('user_id')
    # if request is a post
    if request.method == "POST":
        # check stock entered
        if not request.form.get("symbol"):
            return apology("Please enter a stock Symbol", 400)
        # check postive, none fractional shares of stock entered
        shares = request.form.get("shares")
        # check it's not a decimal entry
        if not shares.isdigit():
            return apology("Please enter a whole number of shares", 400)
        # check it's a positive number
        shares = int(shares)
        if shares < 1:
            return apology("Please enter an postive number of shares", 400)
        # look up share cost
        api_response = lookup(request.form.get("symbol"))
        if not api_response:
            return apology("Share ticker symbol not recognised", 400)
        # work out share cost * quantity selling
        price = (api_response.get("price")) * shares
        stock = request.form.get("symbol")
        # check user has that many shares
        stock_held = db.execute("SELECT SUM(stock_quantity) FROM transactions WHERE user_id=? AND stock=?", user, stock)
        quantity_held = stock_held[0]['SUM(stock_quantity)']
        if shares > quantity_held:
            return apology("Sorry you don't own that many shares of that stock to sell", 400)
        # if user has the shares to sell, then insert new log into transactions + update users cash in users
        else:
            action = "Sell"
            cost_dollars = -abs(price)
            shares_to_remove = -abs(shares)
            timestamp = datetime.datetime.now()
            db.execute("INSERT INTO transactions (user_id, stock, action, cost_dollars, timestamp, stock_quantity) VALUES  (?, ?, ?, ?, ?, ?)", user, stock, action, cost_dollars, timestamp, shares_to_remove)
            # update users funds
            db.execute("UPDATE users SET cash = cash-? WHERE id = ?", cost_dollars, user)
        return index()
    # if it's a get request - render sell page
    else:
        # extract stocks owned by user from database
        user_stocks = db.execute("SELECT DISTINCT stock FROM transactions WHERE user_id=?", user)
        return render_template("sell.html", user_stocks=user_stocks)


@app.route("/add_funds", methods=["GET", "POST"])
@login_required
def add_funds():
    user = session.get('user_id')
    if request.method == "POST":
        if not request.form.get("dollars"):
            return apology("Please enter purchase amount", 400)
        # check postive, none fractional shares of stock entered
        dollars = request.form.get("dollars")
        # check it's not a decimal entry
        if not dollars.isdigit():
            return apology("Please only submit whole dollar amounts", 400)
        # check it's a positive number
        dollars = int(dollars)
        if dollars < 1:
            return apology("Please enter an postive amount", 400)
        deposit = db.execute("UPDATE users SET cash = cash + ?", dollars)
        flash("successfully added $" + str(dollars) + " to your account")
        return render_template("account_settings.html")
    else:
        return render_template("account_settings.html")