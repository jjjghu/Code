// 主頁面輪播圖 開始
document.addEventListener('DOMContentLoaded', () => {
    const slides = document.querySelectorAll('.slider img');
    const navLinks = document.querySelectorAll('.slider-nav a');
    let currentIndex = 0;
    let autoPlayInterval = null;

    function showSlide(index) {
        // 確保slide當中不是空的
        if (slides.length > 0 && slides[index]) {
            let slideWidth = slides[index].clientWidth;
            document.querySelector('.slider').scrollLeft = slideWidth * index;
            updateNav(index);
        }
    }

    // 獲取箭頭
    const prevArrow = document.querySelector('.prev-arrow');
    const nextArrow = document.querySelector('.next-arrow');

    function updateNav(index) {
        navLinks.forEach((link, i) => {
            if (i === index) {
                link.style.backgroundColor = 'rgb(0, 173, 181)';
                link.style.border = '0.1rem solid rgb(0, 173, 181)';
                link.style.opacity = '1';
            }
            else {
                link.style.backgroundColor = '';
                link.style.opacity = '0.75';
                link.style.border = 'none';
            }
        });
    }

    // 跳到下一頁
    function goToNextSlide() {
        currentIndex = (currentIndex + 1) % slides.length;
        showSlide(currentIndex);
    }
    // 跳到上一頁
    function goToPrevSlide() {
        currentIndex = (currentIndex - 1 + slides.length) % slides.length;
        showSlide(currentIndex);
    }

    //  箭頭加入功能
    if (prevArrow) {
        prevArrow.addEventListener('click', (event) => {
            event.preventDefault();
            goToPrevSlide();
        });
    }

    if (nextArrow) {
        nextArrow.addEventListener('click', (event) => {
            event.preventDefault();
            goToNextSlide();
        });
    }


    // 將每個 navLink 加上 click 事件
    if (navLinks) {
        navLinks.forEach((link) => {
            link.addEventListener('click', (event) => {
                const index = parseInt(event.currentTarget.getAttribute('data-index'), 10);
                currentIndex = index;
                showSlide(index);
            });
        });
    }

    // 開始自動播放, 設定微 3000ms 
    function startAutoPlay() {
        autoPlayInterval = setInterval(goToNextSlide, 3000);
    }

    // 停止自動播放
    function stopAutoPlay() {
        if (autoPlayInterval) {
            clearInterval(autoPlayInterval);
        }
    }

    // 初始化
    showSlide(currentIndex);
    startAutoPlay();

    // 滑鼠進入就不播放, 離開就播放
    const sliderWrapper = document.querySelector('.slider-wrapper');
    if (sliderWrapper) {
        sliderWrapper.addEventListener('mouseenter', stopAutoPlay);
        sliderWrapper.addEventListener('mouseleave', startAutoPlay);
    }
    // 主頁面輪播圖結束


    // 登入頁面的眼睛圖示切換功能, 綁訂到 passwordIcon 當中
    // 利用 password text 互相切換
    // 觸發時機為按下圖示的時候
    var passwordIcon = document.getElementById('passwordIcon');
    if (passwordIcon) {
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
    // 黑暗模式切換按鈕, 都在Loaded之後確認按紐存在, 再加入功能
    // toggle不知為何不能使用, 因此使用add remove 判斷做到相同的效果
    var themeIcon = document.getElementById('themeIcon');
    if (themeIcon) {
        themeIcon.onclick = function () {
            document.body.classList.toggle('dark-theme');
            themeIcon.classList.toggle('bx-brightness');
            themeIcon.classList.toggle('bx-moon');
        }
    }

});
// 抓取網頁圖片丟入 preview 當中, 在頁面載入完成之後就做
window.onload = function () {
    // 獲取所有的 .slider.product img 元素
    var images = document.querySelectorAll('.slider.product img');

    // 獲取所有的 .slider-nav.product a 元素
    var navs = document.querySelectorAll('.slider-nav.product a');

    // 確保 images 和 navs 的數量相同
    if (images.length === navs.length) {
        // 為每個 .slider-nav.product a 元素設定背景圖片
        navs.forEach(function (nav, index) {
            // 獲取對應的 .slider.product img 元素的圖片 URL
            var imageUrl = images[index].src;

            // 將 .slider-nav.product a 元素的背景圖片設定為對應的圖片 URL
            nav.style.backgroundImage = 'url(' + imageUrl + ')';
            nav.style.backgroundSize = 'cover';
        });
    }

    // 綁定檢查的內容
    var checkIcon = document.getElementById('check-icon');
    var passwordBox = document.getElementById('password-box');
    var passwordCheck = document.getElementById('password-check');
    if (passwordBox && passwordCheck) {
        passwordBox.addEventListener('input', () => checkPassword(checkIcon, passwordCheck, passwordBox));
        passwordCheck.addEventListener('input', () => checkPassword(checkIcon, passwordCheck, passwordBox));
    }
};
// 判斷兩個inputBox內容是否相同的函數, 相同更改為打勾, 框線變為綠色, 不同就變為紅色
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
/*
每個物件都要加入判斷存不存在, 不然就要確保物件都存在之後將 js 分開寫,
*/