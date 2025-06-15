package com.example.des;


import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.util.Log;
public class MainActivity extends AppCompatActivity {

    // Used to load the 'des' library on application startup.
    static {
        System.loadLibrary("des");
    }

    // 声明 JNI 方法
    public native String desEncrypt(String input);
    public native String desDecrypt();
    private static final String TAG = "rizhi";

    private static final String FLAG_ENCRYPTED = "e0bdb3a5cd8b1a76";  // 示例：加密后的 flag

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText inputFlag = findViewById(R.id.inputFlag);
        final Button checkFlagButton = findViewById(R.id.checkFlagButton);

        checkFlagButton.setOnClickListener(v -> {
            String input = inputFlag.getText().toString();

            if (input.equals(desDecrypt())) {

                Toast.makeText(this, "flag正确", Toast.LENGTH_SHORT).show();
            } else {

                Toast.makeText(this, "flag错误", Toast.LENGTH_SHORT).show();
            }


             // 执行 DES 加密
            // 1. 检查用户输入是否合法

        });
    }

    // 将字节数组转换为十六进制字符串

}