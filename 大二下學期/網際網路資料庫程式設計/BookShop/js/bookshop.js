// 主頁面輪播圖版本 
document.addEventListener('DOMContentLoaded', () => {
    const slides = document.querySelectorAll('.slider img');
    const navLinks = document.querySelectorAll('.slider-nav a');
    let currentIndex = 0;
    let autoPlayInterval = null;

    function showSlide(index) {
        let slideWidth = slides[index].clientWidth;
        document.querySelector('.slider').scrollLeft = slideWidth * index;
        updateNav(index);
    }

    function updateNav(index) {
        navLinks.forEach((link, i) => {
            if (i === index) {
                link.style.border = '0.1rem solid rgb(0, 173, 181)';
                link.style.opacity = '1';
            }
            else {
                link.style.opacity = '0.75';
                // set border to none
                link.style.border = 'none';
            }

        });
    }

    function goToNextSlide() {
        currentIndex = (currentIndex + 1) % slides.length;
        showSlide(currentIndex);
    }

    navLinks.forEach((link) => {
        link.addEventListener('click', (event) => {
            const index = parseInt(event.currentTarget.getAttribute('data-index'), 10);
            currentIndex = index;
            showSlide(index);
        });
    });

    function startAutoPlay() {
        autoPlayInterval = setInterval(goToNextSlide, 3000);
    }

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
    sliderWrapper.addEventListener('mouseenter', stopAutoPlay);
    sliderWrapper.addEventListener('mouseleave', startAutoPlay);
});

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