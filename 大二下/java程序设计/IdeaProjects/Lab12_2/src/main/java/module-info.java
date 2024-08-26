module com.example.lab12_2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab12_2 to javafx.fxml;
    exports com.example.lab12_2;
}