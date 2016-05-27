<form action="account.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="amount">
                <option disabled selected value="">Choose amount</option>
                    <option value='500'>$500</option>
                    <option value='1000'>$1,000</option>
                    <option value='2000'>$2,000</option>
                    <option value='5000'>$5,000</option>
                    <option value='10000'>$10,000</option>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Submit</button>
        </div>
    </fieldset>
</form>
