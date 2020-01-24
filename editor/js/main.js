'use strict';

(function() {

    let nbLamps = 32;
    let lamps = [];
    let frames = [];
    let currentFrame = 0;
    let totalSpan;
    let frameInput;
    let playToken;

    let redrawUI = function() {
        frameInput.value=currentFrame + 1;
        totalSpan.innerHTML = frames.length;

        //console.log(frames[currentFrame]);

        for (let i = 0 ; i < nbLamps ; i++) {
            let isLit = frames[currentFrame][i];

            if (isLit) {
                if (!lamps[i].classList.contains('lit')) {
                    lamps[i].classList.add('lit');
                }
            } else {
                lamps[i].classList.remove('lit');
            }

        }
    };

    let toggleLamp = function () {
        let isLit = !!this.classList.contains('lit');
        let inFrameIndex = this.inFrameIndex;

        frames[currentFrame][inFrameIndex] = !isLit; // toggle lamp state

        if (isLit) {
            this.classList.remove('lit');
        } else {
            this.classList.add('lit');
        }

        //console.log(frame);
    };

    let addFrame = function() {
        let frame = frames[currentFrame].slice(0);
        frames.push(frame);
        currentFrame++;
        redrawUI();
    };

    let removeFrame = function() {

    };

    let prevFrame = function() {
        if (currentFrame > 0) {
            currentFrame--;
        } else {
            currentFrame = frames.length -1;
        }
        redrawUI();
    };

    let nextFrame = function() {
        if (currentFrame < frames.length - 1) {
            currentFrame++;
        } else {
            currentFrame = 0;
        }
        redrawUI();        
    };

    let playAnimation = function() {
        if (frames.length <= 1) return;

        frameInput.readonly = true;

        playToken = setInterval(function() {
            nextFrame();
        },60);
    };

    let stopAnimation = function() {
        frameInput.readonly = false;

        if (playToken !== null) {
            clearInterval(playToken);
            playToken = null;
        }
    };

    let handleInputChange = function() {
        let v = parseInt(this.value,10);

        if (v >= 1 && v <= frames.length) {
            currentFrame = v - 1;
            redrawUI();
        } else {
            this.value = currentFrame + 1;
        }
    };

    let exportAnimation = function() {

        for (let i = 0 ; i < frames.length ; i++) {
            let frame = frames[i];
            let bitStr = "";

            for (let j = 0 ; j < nbLamps ; j++) {
                bitStr += frame[j] ? "1":"0";
            }

            console.log(parseInt(bitStr,2) + ',');
        }

    };

    /**
     *  Init
     **/
    let init = function() {
        totalSpan = document.getElementById('totalframes');
        frameInput = document.getElementById('curframe');

        frames[0] = [];

        for (let i = 0 ; i < nbLamps ; i++) {
            let l = i+1;
            let lamp = document.getElementById("l" + l);

            lamp.inFrameIndex = i; 

            frames[0].push(false);

            lamp.addEventListener('click', toggleLamp);
            //lamp.classList.add('lit');
            lamps.push(lamp);
        }

        //console.log(frames);

        document.getElementById('addframe').addEventListener('click', addFrame);
        document.getElementById('removeframe').addEventListener('click', removeFrame);
        document.getElementById('prevframe').addEventListener('click', prevFrame);
        document.getElementById('nextframe').addEventListener('click', nextFrame);

        document.getElementById('play').addEventListener('click', playAnimation);
        document.getElementById('stop').addEventListener('click', stopAnimation);
        document.getElementById('export').addEventListener('click', exportAnimation);
        frameInput.addEventListener('change', handleInputChange);
    };


    document.addEventListener("DOMContentLoaded", function(event) {
        
        init();


    });

})();