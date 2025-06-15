function desDecrypt() {
    var DES_ecb_encrypt = Module.findExportByName("libdes.so","DES_ecb_encrypt");

    //var getCorrectFlag = Module.findExportByName("libdes.so","__ZN7_JNIEnv17GetStringUTFCharsEP8_jstringPh")
    if(DES_ecb_encrypt !== null) {
        console.log("DES_ecb_encrypt_address: "+ DES_ecb_encrypt)
    }
    Interceptor.attach(DES_ecb_encrypt,{
        onEnter: function(args) {
            //console.log("ax: "+ this.context.eax);
            //console.log("bx: "+ this.context.ebx);       
            //console.log("cx: "+ this.context.ecx);
            var encryptedData = args[0];
            console.log("密文: " + hexdump(encryptedData, { offset: 0, length: 8}));
            //console.log("arg3: "+ Memory.readUtf8String(args[3]))
            //console.log("arg1: "+ Memory.readUtf8String(args[1]));
           // console.log("arg2: "+ Memory.readUtf8String(args[2]));
            //console.log("arg3: "+ Memory.readUtf8String(args[3]));

            //
           
            //console.log("arg1 :"+Memory.readUtf8String(args[0]));
            //var ptr = args[0];
            //console.log("arg2 :"+  ptr);                      
        },
        onLeave: function(retval) {                             
        }
    })
}


function DES_set_key() {
    var set_key = Module.findExportByName("libdes.so","DES_set_key");
    //var getCorrectFlag = Module.findExportByName("libdes.so","__ZN7_JNIEnv17GetStringUTFCharsEP8_jstringPh")
    if(set_key !== null) {
        console.log("DES_set_key_address: "+ set_key)
    }
    Interceptor.attach(set_key,{
        onEnter: function(args) {
            //console.log("ax: "+ this.context.eax);
            //console.log("bx: "+ this.context.ebx);      
            //console.log("cx: "+ this.context.ecx);
            var encryptedData = args[0];
            console.log("DES_sec_key: " + hexdump(encryptedData, { offset: 0, length: 8}));


            //console.log("arg3: "+ Memory.readUtf8String(args[3]))
            //console.log("arg1: "+ Memory.readUtf8String(args[1]));
           // console.log("arg2: "+ Memory.readUtf8String(args[2]));
            //console.log("arg3: "+ Memory.readUtf8String(args[3]));

            //

            
            //console.log("arg1 :"+Memory.readUtf8String(args[0]));
            //var ptr = args[0];
            //console.log("arg2 :"+  ptr);                      
        },
        onLeave: function(retval) {                               
        }
    })
}

//function hexdumpa(ptr, options) {
//    options = options || {};
//    options.length = options.length || 16;
//    options.precision = options.precision || 2;
//    var length = options.length;
//    var precision = options.precision;
//    var result = '';
//    var view = new Uint8Array(ptr.readByteArray(length));
//
//    for (var i = 0; i < length; i++) {
//        result += ('0x' + ('00' + view[i].toString(16)).slice(-precision)) + ' ';
//    }
//    return result.trim();
//}
setTimeout(desDecrypt,2000);

setTimeout(DES_set_key,2000);

