# UI에서의 데이터를 가져와서 활용하기
프로젝트를 처음 만들어서 보면 MainActivity.java 파일은 다음과 같다.
```java
package com.example.androidtest;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
   }
}
```
이 파일의 실행에 대한 내용은 이전에 포스팅한 글 *3-2 어플리케이션 실행*을 참고하길 바란다.     
[3.동작원리](https://l-zzu-h.tistory.com/4) : https://l-zzu-h.tistory.com/4

<br>

우리가 만든 UI 화면은 activity_login.xml 이므로 `setContentView(R.layout.activity_login);`으로 바꾸어 준다.

<br>

---
<br>
이렇게 실행을 하면 UI는 구동이 되어 볼 수 있으나 입력한 데이터를 활용하지 못한다.    
여기서 우리는 입력한 데이터를 받아와 두번째 화면에 출력하는 작업을 해보자.    

다음의 순서에 따라 작업을 한다.
1. activity_login.xml에서 데이터를 읽어오는데 필요한 Inflate의 이름을 지어준다.
2. 해당 Inflate의 데이터를 읽어오고 출력할 화면을 가지는 class에 데이터를 넘겨준다.
3. 받은 데이터를 출력한다.

<br>

작업하기에 앞서 출력할 xml파일과 그 화면을 가지는 class를 미리 만든다.    
xml파일은 기본적으로 생성되었으나 우리가 사용하지 않은 activity_main.xml 파일을 사용하기로 하자.      
class는 LoginActivity.class를 새로 생성한다.   
내용은 MainActivity.class와 동일하게 두고, `setContentView(R.layout.activity_main);`으로 한다.

<br>

---
<br>

## 1. 요소 이름 짓기
이름을 짓는데 약속을 하자.     
Inflate의 명은 Inflate의 요소명과 해당 기능을 합친 것으로 한다.     

예를들어 Email 입력란 같은 경우를 보면
```html
<com.google.android.material.textfield.TextInputLayout
    android:layout_width="match_parent"
    android:layout_height="50dp"
    android:paddingRight="12dp"
    android:paddingLeft="12dp"
    android:layout_marginBottom="20dp"
    >
    <com.google.android.material.textfield.TextInputEditText
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:hint="Email"
        android:id="@+id/TextInputEditText_email"
        />
</com.google.android.material.textfield.TextInputLayout>
```
TextInputEditText라는 요소명과 Email이라는 기능을 합쳐 **TextInputEditText_email**라고 한다.
password도 동일하게 **TextInputEditText_password**라 하며,

입력받은 것을 넘겨 로그인을 위한 버튼은 RelativeLayout으로 만들어져 있으므로 **RelativeLayout_login**이라 한다.

다음으로 표시할 TextView의 이름을 **TextView_get**이라 한다.

이렇게 하는 이유는 각 이름을 구분하기가 쉽고 이후 실수할 일이 적어진다.

<br>

---
<br>

## 2. 데이터를 읽어오고 내보내기
텍스트 입력받는 객체는 TextInputEditText이다. 이 클래스를 import하고 email과 password를 저장할 멤버변수를 만들어준다.    
그리고 데이터를 입력하고 데이터를 넘길 동작의 버튼은 RelativeLayout로 이루어져 있으므로 같이 import를 한다. 이 Layout에 대한 주소를 저장할 멤버변수도 선언한다.
```java
    TextInputEditText TextInputEditText_password, TextInputEditText_email;
    RelativeLayout RelativeLayout_login;
```

이제 xml을 통해 생성된 객체들의 주소를 멤버 변수에 저장해야한다. 이를 위한 메소드는 `findViewById()`이다.    
각 변수에 이 메소드를 이용하여 주소를 저장하자.
```java
TextInputEditText_email = findViewById(R.id.TextInputEditText_email);
TextInputEditText_password = findViewById(R.id.TextInputEditText_password);
RelativeLayout_login = findViewById(R.id.RelativeLayout_login);
```
Layout이 click을 감지하면 받아온 데이터를 출력할 클래스로 보내준다.     
즉 RelativeLayout_login의 **click Listener**을 설정해준다.

```java
RelativeLayout_login.setOnClickListener(new View.OnClickListen() {
    @Override
    public void onClick(View view) {
        String email = TextInputEditText_email.getText().toString();
        String password = TextInputEditText_password.getText().toString()
        Intent intent = new Intent(MainActivity.this, LoginActivity.class);
        intent.putExtra("email", email);
        intent.putExtra("password", password);
        startActivity(intent);
    }
});
```
새 Activity를 실행하기 위해 Intent 객체를 생성한다. 이 매개변수는 Context와 class이다.    
**Intent**는 화면 간 데이터를 전달하기 위한 클래스이다.     
새로운 화면에 현재 얻은 데이터를 전달해야 하므로 이 클래스를 써야한다.     
`intent.putExtra()`메소드는 Data 이름을 저장할 String과 보내줄 Data를 매개변수로 받는다.     
저장된 이름을 통해 받는 Activity에서는 데이터를 꺼내올 수 있다.    

`startActivity(intent);`를 통해 새로운 화면을 가져올 수 있다.

<br>

---
<br>

## 3. 받은 데이터 화면에 출력하기
LoginActivity로 들어와서 여기서도 출력할 TextView의 멤버변수를 만들어준다.    
```java
TextView TextView_get;
TextView_get = findViewById(R.id.TextView_get);
```
<br>

화면전환 되면서 데이터를 Intent 객체로 받는다.     
`Intent intent = getIntent();`    

앞서 `putExtra()` 메소드를 통해 보낼 데이터를 저장했다. 그렇다면 받을 데이터는 `getExtra()`를 통해 받을 수 있다.     
getExtra는 반환 값이 Bundle이므로 Bundle 객체로 받는다.    
`Bundle bundle = intent.getExtras();`    
<br>

이 Bundle을 통해 데이터를 읽어온다. 우리는 String을 Data로 보냈으므로 String으로 데이터를 받는다.

```java
String email = bundle.getString("email");
String password = bundle.getString("password");
```
보낼 때 지정한 데이터 이름을 키로 하여 키에 해당하는 데이터를 받아온다.

마지막으로 TextView에 이 데이터들을 출력해야 한다.     
TextView에 새 text를 저장하는 메소드는 `setText()`이다.
```java
TextView_get.setText("email: "+ email + "\npassword: "+ password);
```
<br>

---
<br>

# 전체 코드 및 출력 화면
```java
//MainActivity.java

package com.example.androidtest;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.style.ClickableSpan;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.google.android.material.textfield.TextInputEditText;

public class MainActivity extends AppCompatActivity {

    TextInputEditText TextInputEditText_password, TextInputEditText_email;
    RelativeLayout RelativeLayout_login;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        TextInputEditText_email = findViewById(R.id.TextInputEditText_email);
        TextInputEditText_password = findViewById(R.id.TextInputEditText_password);
        RelativeLayout_login = findViewById(R.id.RelativeLayout_login);


        RelativeLayout_login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String email = TextInputEditText_email.getText().toString();
                String password = TextInputEditText_password.getText().toString();

                Intent intent = new Intent(MainActivity.this, LoginActivity.class);
                intent.putExtra("email", email);
                intent.putExtra("password", password);
                startActivity(intent);
            }
        });
    }
}
```

```java
//LoginActivity.java

package com.example.androidtest;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;

public class LoginActivity extends AppCompatActivity {

    TextView TextView_get;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView_get = findViewById(R.id.TextView_get);

        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();
        String email = bundle.getString("email");
        String password = bundle.getString("password");

        TextView_get.setText("email: "+ email + "\npassword: "+ password);
   }
}
```
![img](./img/캡처.png)

***

# What is the Inflate?
Inflate 는 사전적 의미로 '부풀리다' 라는 뜻이다.     
안드로이드에서 inflate를 사용하면 xml에 정의되어 있는 view를 실제 view객체로 만드는 역할을 한다. 
