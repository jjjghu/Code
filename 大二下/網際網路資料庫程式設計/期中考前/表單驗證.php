<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
    <title>表單驗證.php</title>
</head>
<script>
    $(document).ready(function ($) {
        $("#form1").submit(function () {
            var message = "";
            var id_check = /[^a-zA-Z0-9]/g;
            var mail_check = /.+@.+\..+/;
            var account = $("#account").val();

            // 帳號判斷
            if (account == "")
                message = "請輸入帳號!!";
            else if (account.indexOf(' ') >= 0)
                message = "帳號不可有空格!!";
            else if (account.length < 6 || account.length > 12)
                message = "帳號長度限制 : 6-12 ";
            else if (account.match(id_check))
                message = "帳號僅限英數字!!";

            if (message) {
                // 顯示錯誤訊息
                $("#message").html(message);
                // 標註錯誤區域
                $("#account").focus();
                // return false 可以阻止表單送出
                return false;
            }

            if ($("#pwd").val().length < 6 || $("#pwd").val().length > 12) {
                $("#message").html("密碼長度限制 : 6-12 ");
                $("#pwd").focus();
                return false;
            }
            if ($("#pwd").val() != $("#pwd2").val()) {
                $("#message").html("2次密碼輸入不相同!!");
                $("#pwd2").focus();
                return false;
            }
            if (!$("#email").val().match(mail_check)) {
                $("#message").html("E-mail格式錯誤!");
                $("#email").focus();
                return false;
            }

            if (!$("input:radio[name=gender]").is(":checked")) {
                $("#message").html("請選擇性別!!");
                $("#gender").focus();
                return false;
            }

            var cnt_hobby = $("input:checkbox:checked[name='hobby[]']").length;
            if (cnt_hobby < 2 || cnt_hobby > 3) {
                $("#message").html("興趣選項限制: 最少2項,最多3項 !");
                return false;
            }

            if ($('#department').val() == 0 || $('#department :selected').text() == "") {
                $("#message").html("請選擇系所 !");
                return false;
            }
            if ($("input:checkbox:checked[name='agree']").length == 0) {
                $("#message").html("是否同意?");
                return false;
            }

            // 網頁通知
            alert("表單驗證成功!!");

        });

        // 全選功能實作
        $("#clickAll").click(function () {
            if ($("#clickAll").prop("checked")) {
                $("input[name='hobby[]']").each(function () {
                    $(this).prop("checked", true);
                });
            } else {
                $("input[name='hobby[]']").each(function () {
                    $(this).prop("checked", false);
                });
            }
        });

    });
</script>
<!-- bootstrap CSS -->
<link rel="stylesheet" href="bootstrap.css">

<body>
    <div class="container">
        <div class="row">
            <div class="col-sm-4 col-sm-offset-4">
                <h2>會員註冊</h2>
                <form class="form-horizontal" role="form" id="form1">
                    <div class="form-group">
                        <label class="col-sm-4 control-label" for="account">帳號</label>
                        <div class="col-sm-8">
                            <input type="text" class="form-control" id="account" name="account" placeholder="限4-10個字">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">密碼</label>
                        <div class="col-sm-8">
                            <input type="password" class="form-control" id="pwd" name="pwd" placeholder="限6-12個字">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">密碼確認</label>
                        <div class="col-sm-8">
                            <input type="password" class="form-control" id="pwd2" name="pwd2" placeholder="">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">E-mail</label>
                        <div class="col-sm-8">
                            <input type="text" class="form-control" id="email" name="email" placeholder="">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">性別</label>
                        <div class="col-sm-8">
                            <input type="radio" class="radio-inline" id="gender1" name="gender">男
                            <input type="radio" class="radio-inline" id="gender2" name="gender">女
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">興趣</label>
                        <div class="col-sm-8">
                            <input type="checkbox" class="checkbox-inline hobby_group" name="hobby[]">跑步
                            <input type="checkbox" class="checkbox-inline hobby_group" name="hobby[]">爬山
                            <input type="checkbox" class="checkbox-inline hobby_group" name="hobby[]">聽音樂
                            <input type="checkbox" class="checkbox-inline hobby_group" name="hobby[]">打球
                            <input name="clickAll" id="clickAll" type="checkbox"> 全選
                            <label for="hobby_4" class="error">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="col-sm-4 control-label">系所</label>
                        <div class="col-sm-8">
                            <select name="department" id="department">
                                <option value="0"></option>
                                <option value="1">資訊工程系</option>
                                <option value="2">電子工程系</option>
                                <option value="3">電機工程系</option>
                                <option value="4">機電工程系</option>
                            </select>
                            <label for="department" class="error">
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="col-sm-8 col-sm-offset-4">
                            <div class="checkbox">
                                <label>
                                    <input type="checkbox" id="agree" name="agree">我同意相關服務條款
                                </label>
                                <label class="error" for="agree"></label>
                            </div>
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="col-sm-7s col-sm-offset-5">
                            <div id="message" class="form-group fw-bold text-danger">錯誤訊息</div>
                            <br>
                            <label>
                                <button type="submit" class="btn btn-primary">送出</button>
                                <button type="reset" class="btn btn-primary">重填</button>
                            </label>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    </div>
</body>

</html>