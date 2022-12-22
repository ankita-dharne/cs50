import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol, name, price, SUM(shares) as totalStocks FROM transactions WHERE user_id = :id GROUP BY symbol", id=user_id)
    res = db.execute("SELECT cash FROM users WHERE id=:id", id=user_id)
    cash = res[0]['cash']

    total = cash
    # logic for determining current price, stock total value and grand total value
    for stock in stocks:
        total += stock['price'] * stock['totalStocks']

    return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # if request made using form submission
    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        quotation = lookup(symbol)
        share = request.form.get("shares")
        # check for validation of stock name

        if not symbol:
            return apology("Please enter symbol.")
        elif not quotation:
            return apology("Unknown Stock symbol, please try again")

        try:
            shares = int(share)
        except:
            return apology("Required valid shares")

        # check the shares are non negative or null
        if shares <= 0:
            return apology("Required valid shares")

        # calculate transaction
        cost = int(shares) * quotation['price']

        # check user's cash for transaction
        result = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        if cost > result[0]["cash"]:
            return apology("Unsufficient funds for transaction")
        else:
            # update cash amount in database
            db.execute("UPDATE users SET cash=cash-:cost WHERE id=:id", cost=cost, id=session["user_id"])
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (:user_id, :name, :shares, :price, :buy, :symbol)", user_id=session["user_id"], name=quotation["symbol"], shares=int(request.form.get("shares")), price=quotation['price'], buy='buy', symbol=symbol)
        return redirect("/")

    # if user uses redirection
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # fetching all transactions of user
    transactions = db.execute("SELECT type, symbol, price, shares, time FROM transactions WHERE user_id=:id", id=session["user_id"])

    if not transactions:
        return apology("No transactions record")

    return render_template("history.html", transactions=transactions, usd=usd)


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
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

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


@app.route("/delete")
def delete():
    """Delete user"""
    user_id = session["user_id"]
    db.execute("DELETE FROM transactions WHERE user_id=:id", id=user_id)
    db.execute("DELETE FROM users WHERE id=:id", id=user_id)
    # Forget any user_id
    session.clear()
    # Redirect user to login form
    return redirect("/")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # if user submits form
    if request.method == "POST":

        symbol = request.form.get("symbol")
        # check the stock name
        if not symbol:
            return apology("Kindly check the stock name")

        quotation = lookup(symbol)

        # check is valid stock name provided
        if not quotation:
            return apology("Stock symbol not valid, please try again")
        return render_template("quoted.html", quote=quotation, usd=usd)

    # stock name is valid
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # if user submits a form
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # check username submission
        if not username:
            return apology("Username required")

        # check password
        elif not password:
            return apology("Password required")

        # check password confirmation submission
        elif not confirmation:
            return apology("Password confirmation required")

        # check if password and password confirmation match
        if password != confirmation:
            return apology("Password and password confirmation does not match.")

        # hash password
        hash = generate_password_hash(password)
        try:
            # add user to database
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, hash)
            return redirect("/")
        except:
            return apology("Username is already registered")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # if user uses form
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user_id = session["user_id"]

        # check for stock symbol and number of shares
        if (not symbol) or (not shares):
            return apology("Required stock symbol and number of shares")

        # check the shares are non negative or null
        if shares <= 0:
            return apology("Required valid shares")

        availability = db.execute("SELECT shares FROM transactions WHERE user_id = :user_id AND symbol=:symbol GROUP BY symbol", user_id=user_id, symbol=symbol)

        # check that number of shares being sold does not exceed quantity in portfolio
        if shares > availability[0]['shares']:
            return apology("You may not sell more shares than you currently hold")

        quotation = lookup(symbol)

        # calculate transaction cost
        cost = shares * quotation['price']

        # calculate transaction cost
        curr_cash = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)[0]['cash']
        # update amount in database
        db.execute("UPDATE users SET cash=:cost WHERE id=:id", cost=curr_cash+cost, id=user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (:user_id, :name, :shares, :price, :sell, :symbol)", user_id=session["user_id"], name=quotation["symbol"], shares=-(shares), price=quotation['price'], sell='sell', symbol=symbol)
        return redirect("/")
    # if user uses redirection
    else:
        # fetch all transactions of user
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id =:user_id GROUP BY symbol", user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)