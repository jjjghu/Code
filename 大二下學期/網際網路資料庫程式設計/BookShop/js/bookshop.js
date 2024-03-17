document.addEventListener('DOMContentLoaded', (event) => {
    // 剛開始為0
    let currentIndex = 0;
    // 獲取所有按鈕連結
    const nav = document.querySelectorAll('.slider-nav a');
    // 紀錄下總共有多少頁面
    const totalSlides = nav.length;
    let autoPlayInterval = null;

    // 跳轉到下一個圖片
    function goToNextSlide() {

        // 更新位置
        currentIndex = (currentIndex + 1) % totalSlides;
        // 按下按鈕
        nav[currentIndex].click();
    }
    function startAutoPlay() {
        if (!autoPlayInterval) {
            autoPlayInterval = setInterval(goToNextSlide, 3000);
        }
    }
    function stopAutoPlay() {
        if (autoPlayInterval) {
            clearInterval(autoPlayInterval);
            autoPlayInterval = null;
        }
    }

    // nav.forEach((link, value, array));

    // 每一個nav都要監聽事件 (當前元素, 當前元素的index)
    nav.forEach((link, index) => {
        link.addEventListener('click', (event) => {
            // 被按下的時候更新currentIndex
            currentIndex = index;
        });
    });

    let observer = new IntersectionObserver((entries, observer) => {
        entries.forEach(entry => {
            // 當元素進入視窗時entry.isIntersecting為true，否則為false
            if (entry.isIntersecting) {
                startAutoPlay();
            } else {
                stopAutoPlay();
            }
        });
    }, { threshold: 0.5 }); // 至少有50%的元素在視窗中

    // 觀察輪播的容器
    observer.observe(document.querySelector('.slider-wrapper'));

    // 啟動自動播放
    startAutoPlay();
    
    // 設定觸發間隔
    // setInterval(goToNextSlide, 3000); // 3000ms = 3 second
});
