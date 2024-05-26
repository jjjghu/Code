let autoPlayInterval = null; // 全域變數, 自動播放使用
document.addEventListener('DOMContentLoaded', () => {
    // 主頁面輪播圖開始
    const slides = document.querySelectorAll('.slider img');
    const navLinks = document.querySelectorAll('.slider-nav a');
    let currentIndex = 0;

    function showSlide(index) {
        // 確保slide當中不是空的
        if (slides.length > 0 && slides[index]) {
            if (slides.length == 1) {
                prevArrow.style.display = 'none';
                nextArrow.style.display = 'none';
            }
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
                link.style.backgroundColor = 'var(--jjjghu-highlight)';
                link.style.border = '0.1rem solid var(--jjjghu-highlight-opacity)';
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
        console.log('start auto play');
        autoPlayInterval = setInterval(goToNextSlide, 3000);
    }

    // 停止自動播放
    function stopAutoPlay() {
        console.log('stopAutoPlay');
        if (autoPlayInterval) {
            clearInterval(autoPlayInterval);
            autoPlayInterval = null;  // 清除 autoPlayInterval
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

    // 獲取縮圖
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
    };
});