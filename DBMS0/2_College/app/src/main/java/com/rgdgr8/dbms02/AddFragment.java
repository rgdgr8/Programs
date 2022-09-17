package com.rgdgr8.dbms02;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.Fragment;

public class AddFragment extends Fragment {
    private static final String[] DCODES = new String[Department.department.length];

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View root = inflater.inflate(R.layout.fragment_add, container, false);

        for (int i = 0; i < Department.department.length; i++) {
            DCODES[i] = Department.department[i].getDcode() + ": " + Department.department[i].getName();
        }

        TextView scode = root.findViewById(R.id.scode);
        Spinner dcode = root.findViewById(R.id.dcode);
        ArrayAdapter<String> adapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_spinner_item, DCODES);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        dcode.setAdapter(adapter);
        TextView name = root.findViewById(R.id.name);
        TextView address = root.findViewById(R.id.address);
        TextView phone = root.findViewById(R.id.phone);

        Button submit = root.findViewById(R.id.submit);
        submit.setOnClickListener(v -> {
            int sc = Integer.parseInt(scode.getText().toString());
            //Log.d("sc", sc + "");
            if (Student.students.contains(new Student(sc, -1, null, null, null))) {
                new AlertDialog.Builder(getActivity())
                        .setTitle("Student with same code already exists")
                        .setNeutralButton("OK", null)
                        .show();
                return;
            }

            /*if (name.getText().toString().equals("") || address.getText().toString().equals("") || phone.getText().toString().equals("")) {
                new AlertDialog.Builder(getActivity())
                        .setTitle("Invalid input(s)")
                        .setNeutralButton("OK", null)
                        .show();
                return;
            }*/

            Student.students.add(new Student(sc, dcode.getSelectedItemPosition() + 1,
                    name.getText().toString(),
                    address.getText().toString(),
                    phone.getText().toString()
            ));
            getFragmentManager().popBackStack();
        });

        Button cancel = root.findViewById(R.id.cancel);
        cancel.setOnClickListener(v -> {
            getFragmentManager().popBackStack();
        });

        return root;
    }
}