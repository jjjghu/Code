<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ajax</title>
</head>

<body>
    <form name="form1">
        <center>
            <img src="https://picsum.photos/200">
            <div style="font-size:13pt;color:blue">使用者註冊</div>
        </center>
        <table width="500" cellspacing="2" cellpadding="2" align="center" style="border: 1 dashed #008080"
            bgcolor="#FFFFE8">
            <tbody>
                <tr>
                    <td width="200" class="c23">請輸入帳號：</td>
                    <td width="300"><span style="margin-left: 1; font-size:12pt"><input type="text" name="p_usr"
                                id="p_usr" maxlength="12" onkeyup="sendRequest()"></span></td>
                </tr>
                <tr>
                    <td class="c23">請輸入密碼：</td>
                    <td><input type="password" name="p_pwdn1" id="p_pwdn1" maxlength="16"></td>
                </tr>
                <tr>
                    <td class="c23">請確認密碼：</td>
                    <td><input type="password" name="p_pwdn2" id="p_pwdn2" maxlength="16"></td>
                </tr>
                <tr>
                    <td class="c23">姓　　　名：</td>
                    <td><input type="text" name="user_name"></td>
                </tr>
                <tr>
                    <td class="c23">身分證字號：</td>
                    <td><input type="text" name="id_no" onkeyup="sendRequest()"></td>
                </tr>
                <tr>
                    <td colspan="2">&nbsp;</td>
                </tr>
                <tr>
                    <td colspan="2" align="center"><input type="button" value="確定送出">　<input type="reset" value="取消重設">　
                    </td>
                </tr>
            </tbody>
        </table>
    </form>
</body>
<script>
    function sendRequest() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                if (this.responseText == 1) document.getElementById('show_msg').innerHTML = '此帳號已存在!';
                else document.getElementById('show_msg').innerHTML = '';
            }
        };
        var url = 'check_account_ajax.php?p_usr=' + document.form1.p_usr.value + '&timeStamp=' + new Date().getTime();
        xhttp.open('GET', url, true);//建立XMLHttpRequest連線要求
        xhttp.send();
    }

</script>

</html>