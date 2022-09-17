package com.rgdgr8.dbms02;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

public class DeleteFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        /*
        for (int i = 0; i < 4; i++) {
            Student.students.add(new Student(i + 1, 1, "", "", ""));
        }
        /*Demo data*/

        View root = inflater.inflate(R.layout.fragment_delete, container, false);

        EditText scode = root.findViewById(R.id.scode);
        Button delete = root.findViewById(R.id.delete);
        TextView student = root.findViewById(R.id.student);

        delete.setOnClickListener(v -> {
            int ind = Student.students.indexOf(new Student(Integer.parseInt(scode.getText().toString()), -1, null, null, null));
            if (ind < 0) {
                student.setText("No such student found");
            } else {
                student.setText(Student.students.get(ind).toString() + "\n\nDeleted");
                Student.students.remove(ind);
            }
        });

        return root;
    }
}