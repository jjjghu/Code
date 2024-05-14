<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<link rel="stylesheet" href="css/bootstrap.min.css">
<link rel="stylesheet" href="css/custom.css">
<link ref="stylesheet" href="css/datatables.min.css">
<link rel="stylesheet" href="css/font-awesome.min.css">
<link rel="stylesheet" href="css/jquery-ui.min.css">
<link rel="stylesheet" href="css/toastr.min.css">

<body>
    <div class="bg-header">
        <img class='ml-5' src="images/logo1.png">
    </div>
    <!-- 導覽區域 -->
    <nav class="navbar navbar-expand-lg subnavbar bg-subnavbar navbar-dark">
        <!-- 切換按鈕開始, 不必要 -->
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
            aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
        </button>
        <!-- 切換按鈕結束 -->
        <!-- 導覽內容開始 -->
        <div class="ml-5 collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav mr-auto">
                <li class="nav-item active">
                    <a class="nav-link" href="#">系統公告 </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#">繳費及銷帳查詢說明</a>
                </li>
                <!-- 下拉選單, 導覽物件開始 -->
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
                        data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        招生簡章
                    </a>
                    <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                        <a class="dropdown-item" href="#">連結1</a>
                        <a class="dropdown-item" href="#">連結2</a>
                        <!-- 分隔線 <div class="dropdown-divider"></div> -->
                        <a class="dropdown-item" href="#">連結3</a>
                    </div>
                </li>
                <!-- 下拉選單, 導覽物件結束 -->
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
                        data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        資料查詢
                    </a>
                    <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                        <a class="dropdown-item" href="#">連結1</a>
                        <a class="dropdown-item" href="#">連結2</a>
                        <!-- 分隔線 <div class="dropdown-divider"></div> -->
                        <a class="dropdown-item" href="#">連結3</a>
                    </div>
                </li>
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
                        data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        報到相關
                    </a>
                    <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                        <a class="dropdown-item" href="#">連結1</a>
                        <a class="dropdown-item" href="#">連結2</a>
                        <!-- 分隔線 <div class="dropdown-divider"></div> -->
                        <a class="dropdown-item" href="#">連結3</a>
                    </div>
                </li>
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button"
                        data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        罕用字說明
                    </a>
                    <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                        <a class="dropdown-item" href="#">連結1</a>
                        <a class="dropdown-item" href="#">連結2</a>
                        <!-- 分隔線 <div class="dropdown-divider"></div> -->
                        <a class="dropdown-item" href="#">連結3</a>
                    </div>
                </li>
            </ul>
        </div>
        <!-- 導覽內容結束 -->
    </nav>
    <!-- 導覽區域結束 -->
    <!-- 推薦函作業開始 -->
    <div class="container">


        <h2 class='mt-5 ml-5'>:::推薦函作業</h2>
        <div class="container subnavbar border p-3 mt-5 ml-5 border-2rem">
            <!-- 表單開始 -->
            <form id="form1">
                <div class="container ">
                    <div class='font-weight-bold'>研究所擬研讀方向</div>
                    <input type='text' class='form-control ' name="enter1" id="enter1">
                    <div id='enter1Err' class='mb-3'></div>
                </div>

                <!-- 推薦人資料開始 -->
                <div class='container'>
                    <!-- 為了讓標題對齊, 畫出 border, padding設定為 0 -->
                    <div class='container-fluid border border-2rem p-0'>
                        <h5 class='bg-grey text-center font-weight-bold py-2'>推薦人資料</h5>
                        <!-- 用container覆蓋掉原本的 padding 設定 -->
                        <div class="container">
                            <table class="table table-bordered text-center" id="dataTable">
                                <tr>
                                    <th>序號</th>
                                    <th id='enter2Err'>姓名</th>
                                    <th id='enter3Err'>服務單位</th>
                                    <th id='enter4Err'>職稱</th>
                                    <th id='enter5Err'>Email</th>
                                </tr>
                                <tr>
                                    <td class="form-number">1</td>
                                    <td class="form-normal"><input type="text" class="form-control" name="enter2"
                                            id="enter2"></td>
                                    <td class="form-normal"><input type="text" class="form-control" name="enter3"
                                            id="enter3"></td>
                                    <td class="form-normal"><input type="text" class="form-control" name="enter4"
                                            id="enter4"></td>
                                    <td class="form-email"><input type="text" class="form-control " name="enter5"
                                            id="enter5"></td>
                                </tr>
                                <!-- <tr>
                                <td class="form-number">
                                    <button class='btn btn-danger' id="removeRowButton">移除</button>2
                                </td>
                                <td class="form-normal"><input type="text" class="form-control" name="enter6"
                                        id="enter6"><span id='enter6Err'></span></td>
                                <td class="form-normal"><input type="text" class="form-control" name="enter7"
                                        id="enter7"><span id='enter7Err'></span></td>
                                <td class="form-normal"><input type="text" class="form-control" name="enter8"
                                        id="enter8"><span id='enter8Err'></span></td>
                                <td class="form-email"><input type="text" class="form-control " name="enter9"
                                        id="enter9"><span id='enter9Err'></span></td>
                            </tr> -->
                            </table>
                        </div>
                    </div>
                </div>
                <!-- 推薦人資料結束 -->
                <!-- 按鈕區域開始 -->
                <div class='container'>
                    <!-- 為了讓標題對齊, 畫出 border, padding設定為 0 -->
                    <div class='container-fluid my-1 d-flex justify-content-center'>
                        <button class='btn btn-success mr-2' id="add">新增一筆</button>
                        <button class='btn btn-warning mr-2' id='cancel'>取消修改</button>
                        <button class='btn btn-primary' id='save' type='submit'>儲存</button>
                    </div>
                </div>
                <!-- 按鈕區域結束 -->
                <!-- 顯示填寫區域 -->

            </form>
            <!-- 表單結束 -->
            <!-- 警告區域開始 -->
            <div class=' container'>
                <!-- 為了讓標題對齊, 畫出 border, padding設定為 0 -->
                <div class='container-fluid border-2rem bg-warning-light py-3'>
                    <span class='text-danger'>注意事項:</span>
                    <ol>
                        <li>最多只能填寫<span class="text-danger"> 2 </span>位推薦人資料，<span
                                class="text-danger"><b>請務必確認所有資料都填寫正確再送出</b>。</span></li>
                        <li><span class="text-danger"><b>「寄發Email」</b>後，推薦人「姓名」、「服務單位」及「職稱」等欄位即不可再修改。</span></li>
                        <li><span class="text-danger"><b>「推薦人讀取」</b>後，推薦人「Email」欄位不可再修改。</span></li>
                        <li><span class="text-danger"><b>@hotmail.com信箱可能會無法正常收信，請避免使用。</b></span>
                    </ol>
                </div>
            </div>
            <!-- 警告區域結束 -->
        </div>
        <!-- 推薦函作業結束 -->
        <!-- 結果顯示開始 -->
        <div class='container'>
            <!-- 為了讓標題對齊, 畫出 border, padding設定為 0 -->
            <div class='container-fluid ml-3 mt-5'>
                <!-- 用container覆蓋掉原本的 padding 設定 -->
                <div class="container">
                    <table class="table table-bordered text-center">
                        <!-- 使用php將上面表單內的文字顯示在上面 -->
                        <?php
                            if ($_SERVER["REQUEST_METHOD"] == "GET") {
                                if(isset($_GET['enter1']))
                                {
                                echo "
                                    <div class='font-weight-bold'>研究所擬研讀方向</div>
                                        ". (isset($_GET['enter1']) ? $_GET['enter1'] : '') ."
                                    <div id='enter1Err' class='mb-3'></div>";
                                echo "
                                    <tr>
                                        <th>序號</th>
                                        <th id='enter2Err'>姓名</th>
                                        <th id='enter3Err'>服務單位</th>
                                        <th id='enter4Err'>職稱</th>
                                        <th id='enter5Err'>Email</th>
                                    </tr>
                                    <tr>
                                        <td class='form-number'>1</td>
                                        <td class='form-normal'>" . (isset($_GET['enter2']) ? $_GET['enter2'] : '') . "</td>
                                        <td class='form-normal'>" . (isset($_GET['enter3']) ? $_GET['enter3'] : '') . "</td>
                                        <td class='form-normal'>" . (isset($_GET['enter4']) ? $_GET['enter4'] : '') . "</td>
                                        <td class='form-email'>" . (isset($_GET['enter5']) ? $_GET['enter5'] : '') . "</td>
                                    </tr>";
                                }

                                if(isset($_GET['enter6']))
                                {
                                    echo"
                                    <tr>
                                        <td class='form-number'>2</td>
                                        <td class='form-normal'>" . (isset($_GET['enter6']) ? $_GET['enter6'] : '') . "</td>
                                        <td class='form-normal'>" . (isset($_GET['enter7']) ? $_GET['enter7'] : '') . "</td>
                                        <td class='form-normal'>" . (isset($_GET['enter8']) ? $_GET['enter8'] : '') . "</td>
                                        <td class='form-email'>" . (isset($_GET['enter9']) ? $_GET['enter9'] : '') . "</td>
                                    </tr>
                                    ";
                                }
                            }
                            ?>
                        <!-- <tr>
                            <th>序號</th>
                            <th id='enter2Err'>姓名</th>
                            <th id='enter3Err'>服務單位</th>
                            <th id='enter4Err'>職稱</th>
                            <th id='enter5Err'>Email</th>
                        </tr>
                        <tr>
                            <td class='form-number'>1</td>
                            <td class=' form-normal'>
                            </td>
                            <td class='form-normal'>
                            </td>
                            <td class=' form-normal'>
                            </td>
                            <td class='form-email'>
                            </td>
                        </tr>
                        <tr>
                            <td class=' form-number'>2</td>
                            <td class='form-normal'></td>
                            <td class=' form-normal'></td>
                            <td class='form-normal'></td>
                            <td class=' form-email'></td>
                        </tr> -->
                    </table>
                </div>
            </div>
        </div>
    </div>
    <!-- 結果顯示結束 -->
    <footer class="bg-footer py-5 ">
        <div class="container" style="color:#fff">
            <address>
                <div class="p-2">機關地址：<a href="https://maps.google.com.tw/maps?q=國立彰化師範大學進德校區">500 彰化市進德路 1 號</a>
                </div>
                <div class="p-2 row">
                    <div class="col-sm-3" style="min-width: max-content;">機關電話：<a href="tel:04-7232105">04-7232105
                            (總機)</a></div>
                    <div class="col-sm-3" style="min-width: max-content;">招生試務：5632~5637(分機)</div>
                </div>
        </div>
        </div>
    </footer>
</body>
<!-- bootstrap JS -->
<script src="js/jquery.min.js"></script>
<script src="js/jquery.validate.js"></script>
<script src="js/jquery-ui.min.js"></script>
<script src="js/additional-methods.js"></script>
<script src="js/additional-methods.min.js"></script>
<script src="js/jquery.print.min.js"></script>
<script src="js/jquery-ui.min.js"></script>

<script src="js/bootstrap.bundle.min.js"></script>
<script src="js/index.js"></script>

</html>