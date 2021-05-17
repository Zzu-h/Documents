지금까지 UI를 완성을 했으나 부족한 점이 있다.
1. 버튼의 이미지 파일을 지정하지 않음
2. AVD 구동 시키고, EditText에 글자 입력할 시 hint가 사라짐

하나씩 수정해 나가보자.

---

## 버튼 이미지 삽입
버튼 하나를 보면, 이미지와 텍스트가 공존한다.    
하지만 버튼 요소는 텍스트를 지정할 수 있으나, 이미지는 삽입이 불가하다.
background를 통해 배경을 이미지화 할 수 있으나, 배경 전체가 이미지로 들어가므로 우리가 목표한 바와는 다르다.

따라서, Button 요소를 버리고 Layout을 통해 이미지와 텍스트를 삽입하자.     
이미지를 보면 텍스트는 가운데 정렬되어 있고, 이미지는 왼쪽으로 치우쳐져 있다.    
우리는 다음과 같이 만드는 것을 목표로 하자.

![buttonImg](./img/button.png)

이렇게 구현하기 위해서는 LinearLayout보다 RelativeLayout으로 배치하는 것이 적절하겠다.    
**RelativeLayout**을 바탕으로 TextView를 깔고 ImageView를 깔아서 생성한다.
```html
<RelativeLayout
    android:id="@+id/RelativeLayout_login"
    android:layout_width="match_parent"
    android:layout_height="50dp"
    android:background="@drawable/btn_blue"
    android:orientation="horizontal"
    android:layout_marginLeft="12dp"
    android:layout_marginRight="12dp"
    android:clickable="true"
    >
    <TextView
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:text="Login"
        android:textColor="#ffffff"
        android:textSize="20sp"
        android:gravity="center"
        />
    <ImageView
        android:layout_width="80dp"
        android:layout_height="40dp"
        android:background="@null"
        android:src="@drawable/icon_profile"
        android:layout_alignParentLeft="true"
        android:layout_centerVertical="true"
        />
</RelativeLayout>
```
ImageView가 왼쪽에 치우치게끔 만들어 주어야 하는데, 기본적으로 왼쪽부터 채워지므로 다른 세팅 없이 두어도 왼쪽 배치가 된다.   
하지만 혹시 모를 경우를 대비하여 왼쪽 배치를 세팅해두자.

이 Layout은 버튼으로써 작용해야 하므로 다음과 같은 세팅을 해야한다.
`android:clickable="true"` 이로써 이 Layout은 클릭이 가능한 버튼이 되었다.

---

## hint 유지하기
TextView를 사용하면 hint가 사라지고 입력이 가능하게 된다.    
우리는 이 hint가 입력란 위에 그대로 유지하게끔 새로 생성해보자.

Android Developer에서 제공하는 desgin 라이브러리를 이용해보자.    
프로젝트에서 **build**.**gadle**(**:app**)에서 다음과 같은 코드를 추가한다.
```java
dependencies{
    ...
    implementation 'com.android.support:design:28.0.0'
    ...
}
```
다음으로 텍스트를 입력할 layout을 생성한다.     
**TextInputLayout**를 생성하여 이 layout 안에 EditText를 삽입하는데, 라이브러리에서 지원하는 EditText를 삽입한다.
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
Password 또한 동일하게 삽입한다.

<br>

---

# 전체 코드 및 실행 화면
```html
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical">
    <TextView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="LOGIN"
        android:textColor="@android:color/holo_blue_dark"
        android:textSize="30sp"
        android:gravity="center"
        android:layout_margin="20dp"
        />
    <ImageView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:background="@null"
        android:src="@drawable/icon_present"
        android:gravity="center"
        android:layout_marginBottom="20dp"
        />

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
            android:hint="Password"
            android:id="@+id/TextInputEditText_password"
            />
    </com.google.android.material.textfield.TextInputLayout>
    <RelativeLayout
        android:id="@+id/RelativeLayout_login"
        android:layout_width="match_parent"
        android:layout_height="50dp"
        android:background="@drawable/btn_blue"
        android:orientation="horizontal"
        android:weightSum="1"
        android:layout_marginLeft="12dp"
        android:layout_marginRight="12dp"
        >
        <!--android:clickable="true"-->
        <TextView
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:text="Login"
            android:textColor="#ffffff"
            android:textSize="20sp"
            android:gravity="center"
            android:layout_weight="1"
            />
        <ImageView
            android:layout_width="80dp"
            android:layout_height="40dp"
            android:background="@null"
            android:src="@drawable/icon_profile"
            android:layout_alignParentLeft="true"
            android:layout_centerVertical="true"
            />

    </RelativeLayout>
    <TextView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="Or"
        android:textSize="24sp"
        android:gravity="center"
        android:layout_margin="20dp"
        />
    <RelativeLayout
        android:layout_width="match_parent"
        android:layout_height="50dp"
        android:background="@drawable/btn_darkblue"
        android:orientation="horizontal"
        android:weightSum="1"
        android:layout_marginLeft="12dp"
        android:layout_marginRight="12dp"
        android:layout_marginBottom="20dp"
        >
        <!--android:clickable="true"-->
        <ImageView
            android:layout_width="80dp"
            android:layout_height="40dp"
            android:background="@null"
            android:src="@drawable/icon_face"
            android:layout_alignParentLeft="true"
            android:layout_centerVertical="true"
            />
        <TextView
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:text="Login with Facebook"
            android:textColor="#ffffff"
            android:textSize="20sp"
            android:gravity="center"
            android:layout_weight="1"
            />
    </RelativeLayout>
    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:orientation="horizontal"
        android:weightSum="10"
        >
        <TextView
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:gravity="center"
            android:layout_weight="3"
            android:textSize="24sp"
            android:text="Find Password"/>
        <TextView
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_weight="7"
            android:gravity="center"
            android:textSize="24sp"
            android:textColor="@android:color/holo_blue_dark"
            android:text="Sign Up"/>
    </LinearLayout>
</LinearLayout>
```
![complete](./img/complete.png)