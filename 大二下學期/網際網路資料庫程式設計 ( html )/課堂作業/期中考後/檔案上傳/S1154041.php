<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>檔案上傳</title>
</head>
<style>
    #Myfile {
        display: none;
    }
</style>

<body>
    <form action='S1154041.php' method='POST' enctype='multipart/form-data'>
        <div>
            <label for='Myfile'>請選擇要上傳的檔案：</label>
            <input type='text' id='filename' readonly>
            <input type='file' name='Myfile' id='Myfile'>
            <button type='button' id="browse">瀏覽</button>
        </div>
        <input type='submit' value='上傳檔案'>
    </form>
    <br>
    <?php
    if (isset($_FILES['Myfile']) && $_FILES['Myfile']['error'] != 4) {
        echo "原始檔案名稱：" . $_FILES['Myfile']['name'];
        echo "<br>伺服器的暫存檔名：" . $_FILES['Myfile']['tmp_name'];
        echo "<br>檔案大小：" . $_FILES['Myfile']['size'];
        echo "<br>檔案的MIME格式:" . $_FILES['Myfile']['type'];
        echo "<br>上傳的錯誤代碼：" . $_FILES['Myfile']['error'];
        echo "<br>";
        if (move_uploaded_file($_FILES['Myfile']['tmp_name'], "c:/upload/" . $_FILES['Myfile']['name']))
            echo "上傳成功";
        else
            echo "上傳失敗";
    } else
        echo "沒有檔案"
            ?>
    </body>
    <script>
        document.getElementById('Myfile').addEventListener('change', function () {
            document.getElementById('filename').value = this.files[0].name;
        });

        document.getElementById('browse').addEventListener('click', function () {
            document.getElementById('Myfile').click();
        });
    </script>

    </html>
    <!-- 刪除資料 -->
    <?php
    // $filename = "c:/upload/" . $_FILES['Myfile']['name'];
    
    // if (file_exists($filename)) {
    //     if (unlink($filename)) {
    //         echo "檔案已成功刪除";
    //     } else {
    //         echo "檔案刪除失敗";
    //     }
    // } else {
    //     echo "檔案不存在";
    // }
    ?>