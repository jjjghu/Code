function checkPassword(checkIcon, passwordCheck, passwordBox) {
    if (passwordBox.value === passwordCheck.value && passwordBox.value != "") {
        checkIcon.className = 'bx bx-check icon-left';
        checkIcon.style.color = 'yellowgreen';
        passwordCheck.style.border = '2px solid yellowgreen';
    } else {
        checkIcon.className = 'bx bx-x icon-left';
        checkIcon.style.color = 'var(--jjjghu-orange)';
        passwordCheck.style.border = '2px solid var(--jjjghu-orange)';
    }
    // 主控台輸出兩者的數值
    // console.log(passwordBox.value, passwordCheck.value, passwordBox.value === passwordCheck.value && passwordBox.value != "");
}
document.addEventListener('DOMContentLoaded', () => {
    // 顯示輸入密碼
    var passwordIcon = document.getElementById('passwordIcon');
    if (passwordIcon) {
        console.log("I got this!");
        passwordIcon.onclick = function () {
            var enter = document.getElementById('password-box');
            if (enter) {
                if (enter.type === 'password') {
                    enter.type = 'text';
                    passwordIcon.className = 'bx bx-show icon-right';
                } else {
                    enter.type = 'password';
                    passwordIcon.className = 'bx bx-hide icon-right';
                }
            }
        };
    }
    // 停用複製貼上
    var passwordBox = document.getElementById('password-box');
    var passwordCheck = document.getElementById('password-check');
    [passwordBox, passwordCheck].forEach(function (element) {
        if (element) {
            element.addEventListener('paste', function (e) {
                e.preventDefault();
            });
            element.addEventListener('copy', function (e) {
                e.preventDefault();
            });
        }
    });
    // 偵測輸入對不對, 後面改成使用表單驗證處理
    window.onload = function () {
        // 綁定檢查的內容
        var checkIcon = document.getElementById('check-icon');
        var passwordBox = document.getElementById('password-box');
        var passwordCheck = document.getElementById('password-check');
        if (passwordBox && passwordCheck) {
            passwordBox.addEventListener('input', () => checkPassword(checkIcon, passwordCheck, passwordBox));
            passwordCheck.addEventListener('input', () => checkPassword(checkIcon, passwordCheck, passwordBox));
        }
    };
    // 按下按鈕的時候, 前往下一步
    // 獲取 id: step1 下面的 class:btn 按鈕
    var step1 = document.getElementById('step1');
    if (step1) {
        var btn = step1.getElementsByClassName('btn');
        if (btn.length > 0)
        {
            // 綁定點擊事件
            btn[0].addEventListener('click', function () {
                // 獲取 id: step2
                var step2 = document.getElementById('step2');
                if (step2) {
                    // 顯示 step2
                    step2.style.display = 'block';
                    // 隱藏 step1
                    step1.style.display = 'none';
                }
            });
        }
    }

});
