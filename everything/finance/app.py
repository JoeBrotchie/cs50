import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

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
    # veriable for user_id
    user_id = session["user_id"]

    # Get cash from user
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    # Make cash an int not a list
    cash = int(cash[0]["cash"])

    # create veriable (account)
    account = cash

    # get db of all user stocks
    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?", user_id)

    for stock in stocks:

        # Look up curent price of stock and store in veriable
        price = lookup(stock["symbol"])["price"]

        # calculate total price if shares of stock
        total = price * int(stock["shares"])

        # calculate total money on account
        account += total

        # update veriable with price and total
        stock["price"] = price
        stock["total"] = total

    # render index.html
    return render_template("index.html", stocks=stocks, cash=cash, account=account)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Ensure stock symbol was real
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("invalid symbol", 400)

        # Ensure buy was submitted
        if not request.form.get("shares"):
            return apology("must provide the amount you want to buy", 400)

        # set buy
        buy = request.form.get("shares")

        # set user_id
        user_id = session["user_id"]

        # set symbol
        symbol = request.form.get("symbol")

        # Ensure the user buys more then 0 of a stock
        if buy.isnumeric() is False:
            return apology("must buy a possitive number", 400)

        # make buy an int
        buy = int(buy)

        if buy == 0:
            return apology("must buy more then 0", 400)

        # Get the amount of money the user has
        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # make it not a list
        cash = row[0]["cash"]

        # Check if he can buy the quantaty they want to buy
        balance = cash - buy * quote["price"]

        if balance < 0:
            return apology("not anuff money", 400)

        # Update cash amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)

        # Insert buy order into history
        db.execute("INSERT INTO history (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)" , user_id, symbol, buy, quote["price"], datetime.now())

        # Query the database for symbol
        query_symbol = db.execute("SELECT symbol FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

        # If user has stocks in that company already
        if len(query_symbol) > 0:

            # Query the database for shares
            shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

            # Make it not a list
            shares = shares[0]["shares"]

            # add up shares
            share_total = shares + buy

            # update the amount of stocks the user owns
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", share_total, user_id, symbol)

        # If user has no stocks in that company
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)" , user_id, symbol, buy)

        #Show user that the stock was bought
        flash("Bought!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history =   db.execute("SELECT symbol, shares, price, timestamp FROM history WHERE user_id = ? ORDER BY timestamp DESC", session["user_id"])

    return render_template("history.html", history=history)

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """update cash amount"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure add_cash was submitted
        if not request.form.get("add_cash"):
            return apology("must provide the amount you want to add", 400)

        # set add_cash
        add_cash = request.form.get("add_cash")

        # make sure user input is a posotive number
        if add_cash.isnumeric() is False:
            return apology("must add a posotive number", 400)

        # make add_cash an int
        add_cash = int(add_cash)

        # make sure user is add more then 0 cash
        if add_cash == 0:
            return apology("must add more then 0", 400)

        # set user_id
        user_id = session["user_id"]

         # Get the amount of money the user has
        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # make it not a list
        cash = row[0]["cash"]

        # make cash an int
        cash = int(cash)

        # calculate total cash of user
        total_cash = cash + add_cash

        # update users cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", total_cash, user_id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("cash.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

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
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol")

        #checking if stock quote is real
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("invalid symbol", 400)

        #if quote is real show the price of it
        else:
            return render_template("quoted.html", price=quote["price"], name=quote["name"])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password and password confirmation was the same
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and password confirmation not the same", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exists
        if len(rows) == 1:
            return apology("already existing username", 400)

        #hash password and put username and hashed password in db
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        #redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Ensure stock symbol was real
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("invalid symbol", 400)

        # Ensure sell was submitted
        if not request.form.get("shares"):
            return apology("must provide the amount you want to sell", 400)

        # set sell
        sell = request.form.get("shares")

        # set user_id
        user_id = session["user_id"]

        # set symbol
        symbol = request.form.get("symbol")

        # Ensure the user sells more then 0 of a stock
        if sell.isnumeric() is False:
            return apology("must be a posotive number", 400)

        # make sell and int
        sell = int(sell)

        if sell == 0:
            return apology("must sell more then 0", 400)

        # Query the database for symbol
        query_symbol = db.execute("SELECT symbol FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

        # check if user has stocks in that company already
        if len(query_symbol) == 0:
            return apology("dont have any shares in that company", 400)

        else:
            # query how many shares the user has in that stock
            shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

            # make it not a list
            shares = shares[0]["shares"]

            # make sure they have anuff shares to sell
            if shares >= sell:

                # calculate new share total
                share_total = shares - sell

                # update share total
                db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", share_total, user_id, symbol)

            else:
                return apology("dont have anuff shares in that company", 400)


        # Get the amount of money the user has
        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # make it not a list
        cash = row[0]["cash"]

        # calculate new balance
        balance = cash + sell * quote["price"]

        # Update cash amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)

        # make sell negative
        sell = sell * -1

        # Insert buy order into history
        db.execute("INSERT INTO history (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)" , user_id, symbol, sell, quote["price"], datetime.now())

        #Show user that the stock was bought
        flash("Sold!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # set user_id
        user_id = session["user_id"]

        # query for all symbols of user
        symbols = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", user_id)

        # render sell.html with all symbols
        return render_template("sell.html", symbols= [row["symbol"] for row in symbols])
