<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP表格</title>
</head>
<style>
    body
    {
        font-size:18px;
    }
    table
    {
        /* 表格寬度設定 */
        width:30vw;
        /* 表格邊界設定 */
        border:1px solid black;
        /* 表格文字置中 */
        text-align: center;
    }
    td
    {
        /* 固定寬度, 避免數字大小影響 */
        width:10vw;
        border:1px solid black;
    }
    /* 第三個td背景顏色設定為紅色, 文字藍 */
    td:nth-child(3)
    {
        color:blue;
        background-color: pink;
    }
</style>
<body>
    <!-- 建立一個 3 * 9 的 table (input, 固定數, 結果)-->
    <form name="MyForm1" action="" method="POST">
        請輸入一個數字 <input type = "text" name="enter"><input type = "submit" value = "送出">
    </form>
    <table>
        <?php
        // 若 enter 有被設定 將 number 以int的型態設定為 enter, 否則設為 0
        $number = isset($_POST['enter']) ? intval($_POST['enter']) : 0;
        for ($i = 1; $i <= 9; $i++)
        {
            // 相乘的結果
            $result = $number * $i;
            //表格開頭
            echo "<tr>";
            // 表格內容 (input, 固定數, 結果)
            echo "<td>{$number}</td><td>{$i}</td><td>{$result}</td>";
            // 表格結尾
            echo "</tr>";
        }
        ?>
    </table>
</body>
</html>