'use strict';

(function() {

    let nbLamps = 32;
    let lamps = [];
    let frames = [];
    let currentFrame = 0;
    let totalSpan;
    let frameInput;
    let playToken;

    /**
     * Refresh the UI
     */
    let redrawUI = function() {
        frameInput.value=currentFrame + 1;
        totalSpan.innerHTML = frames.length;

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

    /**
     * Toggle a lamp on/off
     */
    let toggleLamp = function () {
        let isLit = !!this.classList.contains('lit');
        let inFrameIndex = this.inFrameIndex;

        frames[currentFrame][inFrameIndex] = !isLit; // toggle lamp state

        if (isLit) {
            this.classList.remove('lit');
        } else {
            this.classList.add('lit');
        }
    };

    /**
     * Add a frame at the end of the animation (use the last frame as template)
     */
    let addFrame = function() {
        let frame = frames[frames.length -1].slice(0);
        frames.push(frame);
        currentFrame = frames.length -1;
        redrawUI();
    };
    
    /**
     * Insert frame after the current frame (copy the current frame)
     */
	let insertFrame = function() {
		if (currentFrame === frames.length - 1) {
			addFrame();
		} else {
			let frame = frames[currentFrame].slice(0);
			frames.splice(currentFrame, 0, frame);
			currentFrame++;
			redrawUI();
		}
	};

    /**
     * Remove current frame (or reset the last frame if only one frame left)
     */
    let removeFrame = function() {
        // If it is the last frame then empty it
        if (frames.length === 1) {
			let frame = [];
			for (let i = 0 ; i < nbLamps ; i++) {
				frame.push(false);
			}
            frames = [frame];

            currentFrame = 0

        // otherwise strip it    
        } else {
			frames.splice(currentFrame, 1);
            
            if (currentFrame > 0) {
                currentFrame--;
            }
        }

        redrawUI();
    };

    /**
     * Animation : deacrese current frame count and refresh the UI
     * Used by the UI '<' button
     */
    let prevFrame = function() {
        if (currentFrame > 0) {
            currentFrame--;
        } else {
            currentFrame = frames.length -1;
        }
        redrawUI();
    };

    /**
     * Animation : increase current frame count and refresh the UI
     * Used by setInterval and the UI '>' button
     */
    let nextFrame = function() {
        if (currentFrame < frames.length - 1) {
            currentFrame++;
        } else {
            currentFrame = 0;
        }
        redrawUI();
    };

    /**
     * Start playing the animation starting from the current frame
     */
    let playAnimation = function() {
        if (frames.length <= 1) return;

        frameInput.readonly = true;

        playToken = setInterval(function() {
            nextFrame();
        },60);
    };

    /**
     * Cancel the interval to stop the animation
     */
    let stopAnimation = function() {
        frameInput.readonly = false;

        if (playToken !== null) {
            clearInterval(playToken);
            playToken = null;
        }
    };

    /**
     * Handle UI events coming from the text input
     */
    let handleInputChange = function() {
        let v = parseInt(this.value,10);

        if (v >= 1 && v <= frames.length) {
            currentFrame = v - 1;
            redrawUI();
        } else {
            this.value = currentFrame + 1;
        }
    };

    /**
     * Convert the array of boolean to an array of int values
     */
    let exportAnimation = function() {

        for (let i = 0 ; i < frames.length ; i++) {
            let frame = frames[i];
            let bitStr = "";

            for (let j = 0 ; j < nbLamps ; j++) {
                bitStr += frame[j] ? "1":"0";
            }

			// Export int to string of bits
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
            lamps.push(lamp);
        }

        document.getElementById('addframe').addEventListener('click', addFrame);
		document.getElementById('insertframe').addEventListener('click', insertFrame);
        document.getElementById('removeframe').addEventListener('click', removeFrame);
        document.getElementById('prevframe').addEventListener('click', prevFrame);
        document.getElementById('nextframe').addEventListener('click', nextFrame);

        document.getElementById('play').addEventListener('click', playAnimation);
        document.getElementById('stop').addEventListener('click', stopAnimation);
        document.getElementById('export').addEventListener('click', exportAnimation);
        frameInput.addEventListener('change', handleInputChange);
    };


    // Wait for the DOM to be ready
    document.addEventListener("DOMContentLoaded", function(event) {
        init();
    });

})();