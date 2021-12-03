// let maxi = maximilian();
// let audio = new maxi.maxiAudio();
// let song = new maxi.maxiSample();

var osc1 = new Maximilian.maxiOsc();
var osc2 = new Maximilian.maxiOsc();
  
function play() 
{
    return (osc1.saw(1)) * 1;
}
 //     var osc4 = new Maximilian.maxiOsc(); 
// function play() 
// {
//     return osc1.saw(1)*a + osc2.saw(a*b*0.1)*b
//     if (a++>b)
//     {
//         return;
//    }
// }

// audio.init();

// audio.loadSample('', song);

// audio.play = function()
// {
//     return song.play();
// }