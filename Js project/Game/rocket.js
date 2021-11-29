let scene, camera, render, ConeGeometry, cylinder, Octahedron;

var controls;
var objects = [];
var raycaster;
var blocker = document.getElementById( 'blocker' );
var instructions = document.getElementById( 'instructions' );

var havePointerLock = 'pointerLockElement' in document || 'mozPointerLockElement' in document || 'webkitPointerLockElement' in document;
    if ( havePointerLock ) {
        var element = document.body;
        var pointerlockchange = function ( event ) {
            if ( document.pointerLockElement === element || document.mozPointerLockElement === element || document.webkitPointerLockElement === element ) {
                controlsEnabled = true;
                controls.enabled = true;
                blocker.style.display = 'none';
            } else {
                controls.enabled = false;
                blocker.style.display = '-webkit-box';
                blocker.style.display = '-moz-box';
                blocker.style.display = 'box';
                instructions.style.display = '';
            }
        };
        var pointerlockerror = function ( event ) {
            instructions.style.display = '';
        };
        // Hook pointer lock state change events
        document.addEventListener( 'pointerlockchange', pointerlockchange, false );
        document.addEventListener( 'mozpointerlockchange', pointerlockchange, false );
        document.addEventListener( 'webkitpointerlockchange', pointerlockchange, false );
        document.addEventListener( 'pointerlockerror', pointerlockerror, false );
        document.addEventListener( 'mozpointerlockerror', pointerlockerror, false );
        document.addEventListener( 'webkitpointerlockerror', pointerlockerror, false );
        instructions.addEventListener( 'click', function ( event ) {
            instructions.style.display = 'none';
            // Ask the browser to lock the pointer
            element.requestPointerLock = element.requestPointerLock || element.mozRequestPointerLock || element.webkitRequestPointerLock;
            if ( /Firefox/i.test( navigator.userAgent ) ) {
                var fullscreenchange = function ( event ) {
                    if ( document.fullscreenElement === element || document.mozFullscreenElement === element || document.mozFullScreenElement === element ) {
                        document.removeEventListener( 'fullscreenchange', fullscreenchange );
                        document.removeEventListener( 'mozfullscreenchange', fullscreenchange );
                        element.requestPointerLock();
                    }
                };
                document.addEventListener( 'fullscreenchange', fullscreenchange, false );
                document.addEventListener( 'mozfullscreenchange', fullscreenchange, false );
                element.requestFullscreen = element.requestFullscreen || element.mozRequestFullscreen || element.mozRequestFullScreen || element.webkitRequestFullscreen;
                element.requestFullscreen();
            } else {
                element.requestPointerLock();
            }
        }, false );
    } else {
        instructions.innerHTML = 'Your browser doesn\'t seem to support Pointer Lock API';
    }


    var controlsEnabled = false;
	var moveForward = false;
	var moveBackward = false;
	var moveLeft = false;
    var moveRight = false;
    var canJump = false;
    var prevTime = performance.now();
    var velocity = new THREE.Vector3();

    var playerDirection = 0;//angles 0 - 2pi
    var dVector;
    var angularSpeed = 0.01;
    var playerSpeed = 0.075;
    var playerBackwardsSpeed = playerSpeed * 0.4;
    var rocket_position = 200;

          function init()
          {
            scene = new THREE.Scene();
            
            camera = new THREE.PerspectiveCamera(
                60,
                window.innerWidth/window.innerHeight,
                45,
                15000
            );

            //camera.position.set(50,30,8000);
            camera.position.x = 500;
            camera.position.y = 500;
            camera.position.z = 2500;

            renderer = new THREE.WebGLRenderer({ antialias:true });

            renderer.setSize(window.innerWidth, window.innerHeight);

            document.body.appendChild(renderer.domElement);

            
            //control camera and limit the zoom 
            let controls = new THREE.OrbitControls(camera);
            controls.addEventListener('change', renderer);
            controls.minDistance = 500;
            controls.maxDistance = 2500;

            // let controls = new PointerLockControls(camera, document.body);
            // scene.add( controls.getObject());
            
            //Big sky box?  
            //box
            let materialArray = [];
//             let material22 = [];
//             let material33 = [];
//          var myTextureLoader = new THREE.TextureLoader();
//   var myTexture = myTextureLoader.load('eyeball.png');
//   var material = new THREE.MeshBasicMaterial({map: myTexture});
            
            
            let texture_ft = new THREE.TextureLoader().load( './blizzard_ft.jpg');
            let texture_bk = new THREE.TextureLoader().load( './blizzard_bk.jpg');
            let texture_up = new THREE.TextureLoader().load( './blizzard_up.jpg');
            let texture_dn = new THREE.TextureLoader().load( './blizzard_dn.jpg');
            let texture_rt = new THREE.TextureLoader().load( './blizzard_rt.jpg');
            let texture_lf = new THREE.TextureLoader().load( './blizzard_lf.jpg');
            //top
//            var myTextureLoader = new THREE.TextureLoader();
//            var myTexture = myTextureLoader.load('sky.jpeg');
            let uni = new THREE.TextureLoader().load('./uni.jpeg');
            let metal = new THREE.TextureLoader().load('./metal.jpg');
            
            
            //box
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_ft }));
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_bk }));
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_up }));
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_dn }));
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_rt }));
            materialArray.push(new THREE.MeshBasicMaterial( { map: texture_lf }));
            //top
            materialArray.push(new THREE.MeshBasicMaterial( { map: uni }));

   
            for (let i = 0; i < 6; i++)
            {
                materialArray[i].side = THREE.BackSide;
            }
           
            let skyboxGeo = new THREE.BoxGeometry( 10000, 10000, 10000);
            let skybox = new THREE.Mesh( skyboxGeo, materialArray );
            scene.add( skybox );
            
            //floor
            let floorGeometry = new THREE.PlaneGeometry(10000, 10000, 50, 50);
            floorGeometry.rotateX( - Math.PI / 2);

			const floorMaterial = new THREE.MeshBasicMaterial( { map: texture_dn } );
            const floor = new THREE.Mesh( floorGeometry, floorMaterial);
            scene.add(floor);

            
            // //Add Top
            // const geometry = new THREE.ConeGeometry( 30, 40, 32 );
            // const material = new THREE.MeshBasicMaterial( {color:0xffff00  } );
            // const cone = new THREE.Mesh( geometry, material );
            // //let ConeGeometry.position = ()
            // cone.position.set(0, 540, 0);
            // scene.add( cone );  
          
            
            
            
            // //body
            // const geometry2 = new THREE.CylinderGeometry( 30 , 50, 100, 52 );
            // const material2 = new THREE.MeshBasicMaterial( {color: 0x00000ff} );
            // const cylinder = new THREE.Mesh( geometry2, material2 );
            // cylinder.position.set(0, 400, 0);
            // scene.add( cylinder );
            
            
            //OctahedronGeometry
            const geometry3 = new THREE.CylinderGeometry( 50 , 50, 400, 60 );
            const material3 = new THREE.MeshBasicMaterial( {map: metal} );
            const cylinder2 = new THREE.Mesh( geometry3, material3 );
//            let skybox = new THREE.Mesh( skyboxGeo, material33 );
            //cylinder2.position.set(0, 200, 0);

                cylinder2.position.x = 0;
                cylinder2.position.y = rocket_position;
                cylinder2.position.z = 0;

                scene.add( cylinder2 );
            
                var onKeyDown = function ( event ) {
					switch ( event.keyCode ) {
						case 38: // up
						case 87: // w
							moveForward = true;
							break;
						case 37: // left
						case 65: // a
							moveLeft = true; 
                            break;
						case 40: // down
						case 83: // s
							moveBackward = true;
							break;
						case 39: // right
						case 68: // d
							moveRight = true;
							break;
					}
				};
				var onKeyUp = function ( event ) {
					switch( event.keyCode ) {
						case 38: // up
						case 87: // w
							moveForward = false;
							break;
						case 37: // left
						case 65: // a
							moveLeft = false;
							break;
						case 40: // down
						case 83: // s
							moveBackward = false;
							break;
						case 39: // right
						case 68: // d
							moveRight = false;
							break;
					}
				};


            dVector = new THREE.Vector3(0, 200, 0);
            camera.lookAt(dVector);
            
            
            
            
            animate();
            }


            // function moveForward(speed){
            //     var delta_x = speed * Math.cos(playerDirection);
            //     var delta_z = speed * Math.sin(playerDirection);
            //     var new_x = camera.position.x + delta_x;
            //     var new_z = camera.position.z + delta_z;
            //     camera.position.x = new_x;
            //     camera.position.z = new_z;
            
            //     var new_dx = dVector.x + delta_x;
            //     var new_dz = dVector.z + delta_z;
            //     dVector.x = new_dx;
            //     dVector.z = new_dz;
            //     camera.lookAt( dVector );    
            
            // }

            // function setPlayerDirection(){
            //     //direction changed.
            //     var delta_x = playerSpeed * Math.cos(playerDirection);
            //     var delta_z = playerSpeed * Math.sin(playerDirection);
            
            //     var new_dx = camera.position.x + delta_x;
            //     var new_dz = camera.position.z + delta_z;
            //     dVector.x = new_dx;
            //     dVector.z = new_dz;
            //     console.log(dVector);
            //     camera.lookAt( dVector ); 
            // }
            
            function animate(){
                
                renderer.render(scene, camera);
                //updatePlayer();
                if (controlsEnabled)
                {
                    if ( moveForward ) rocket_position++;
					if ( moveBackward ) rocket_position--;
					if ( moveLeft ) rocket_position--;
					if ( moveRight ) rocket_position--;
                }
                requestAnimationFrame(animate)
            }

            init();