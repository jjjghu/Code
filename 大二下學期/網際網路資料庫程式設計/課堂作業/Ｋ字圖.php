<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ｋ字圖</title>
</head>
<style>
    body
    {
        font-size:18px;
    }
</style>
<body>
    <!-- 輸入區域 -->
    <form>
        <p>請輸入數字<input type="text" name="enter"><button type="submit">送出</button></p>
    </form>
    <?php
        // 獲取輸入, 沒有輸入則設定為 0
        $number = isset($_POST['enter']) ? intval($_POST['enter']) : 0;
        // 輸出 K 字圖
        for ($i = 0; $i <= 2*$number;$i++)
        {
            echo "********";
            for ($j = 0; $j < abs($number-$i);$j++)
            {
                echo "&nbsp;&nbsp;&nbsp;&nbsp;";
            }
            echo "********";
            echo "<br>";
        }
    ?>
</body>
</html>