<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total cost</th>
        </tr>
    </thead>

    <tbody>
        <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["transaction"] ?></td>
            <td><?= $position["timestamp"] ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= number_format($position["price"],2) ?></td>
            <td>$<?= number_format($position["shares"]*$position["price"],2) ?></td>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>

<form action="history.php" method="post">
    <fieldset>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Clear history</button>
        </div>
    </fieldset>
</form>