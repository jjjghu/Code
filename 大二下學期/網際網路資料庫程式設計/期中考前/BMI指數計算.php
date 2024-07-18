<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BMI指數計算</title>
</head>
<style>
    table
    {
        margin-left: 5vw;
        font-size:18px;
    }
    table h3
    {
        margin:0;
        text-align:center;
    }
    td
    {
        width:10vw;
    }
    .blue
    {
        color:blue;
        
        margin:0;
    }

</style>
<body>
    <!-- 2 * 6的 table -->
    <table>
        <form name="MyForm1" action="" method="POST">
            <tr>
                <td></td>
                <td><h3 class="blue">BMI指數計算<h3></td>
            </tr>
            <tr>
                <td>身高(公分)</td>
                <td><input type="text" name = "height"></td>
            </tr>
            <tr>
                <td>體重(公斤)</td>
                <td><input type="text" name = "weight"></td>
            </tr>
            <tr>
                <td></td>
                <td><button type = "submit" method = "post">開始診斷</button></td>
            </tr>

        </form>
        <tr>
            <td>指數</td>
            <td class="blue" id = "BMI"></td>
        </tr>
        <tr>
            <td>診斷結果</td>
            <td class="blue" id = "result"></td>
        </tr>
        <tr>
            <td>理想體重</td>
            <td class="blue" id = "ideal_weight"></td>
        </tr>
    </table>
    <?php
    // 若 height 和 weight 有被設定 將 height 和 weight 以int的型態設定為 height 和 weight, 否則設為 0
    $height = isset($_POST['height']) ? doubleval($_POST['height']) : 0;
    $weight = isset($_POST['weight']) ? doubleval($_POST['weight']) : 0;
    if($height != 0 && $weight != 0)
    {
        $height = $height / 100;
        $BMI = $weight / ($height * $height);
        // 將 id 為 BMI的 td 當中顯示 BMI 的值, 用 php 執行 javascript
        echo "<script>document.getElementById('BMI').innerHTML = '" . $BMI . "';</script>";
        //不能使用多個 ? $result = $BMI>=35? "重度肥胖": $BMI>=30? "肥胖": $BMI>=25? "過重": $BMI>=18.5? "正常": "過輕";
        if($BMI>=35)
            $result = "重度肥胖";
        else if($BMI>=30)
            $result = "中度肥胖";
        else if($BMI>=27)
            $result = "輕度肥胖";
        else if ($BMI >= 24)
            $result = "過重";
        else if($BMI>=18.5)
            $result = "正常範圍";
        else
            $result = "體重過輕";
        // php: 將 id 為 result 的 td 當中顯示 result 的值, 用 php 執行 javascript
        // js: 獲取 id 為 result 的物件, 將裡面的 HTML 設定為 result 的值
        echo "<script>document.getElementById('result').innerHTML = '" . $result . "';</script>";
        echo "<script>document.getElementById('ideal_weight').innerHTML = '" . $height*$height*22 . "公斤';</script>";
    }
    ?>
</body>
</html>