module com.example.notepad {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.notepad to javafx.fxml;
    exports com.example.notepad;
}