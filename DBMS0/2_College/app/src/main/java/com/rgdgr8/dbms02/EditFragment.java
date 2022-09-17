package com.rgdgr8.dbms02;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.Fragment;

public class EditFragment extends Fragment {
    private static final String[] DCODES = new String[Department.department.length];
    int ind = -1;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        /**/
        for (int i = 0; i < 4; i++) {
            Student.students.add(new Student(i + 1, 1, "", "", ""));
        }
        /*Demo data*/

        View root = inflater.inflate(R.layout.fragment_edit, container, false);

        for (int i = 0; i < Department.department.length; i++) {
            DCODES[i] = Department.department[i].getDcode() + ": " + Department.department[i].getName();
        }

        EditText scode = root.findViewById(R.id.scode);
        Button search = root.findViewById(R.id.search);
        TextView tv = root.findViewById(R.id._404);
        search.setOnClickListener(v -> {
            tv.setVisibility(View.INVISIBLE);
            ind = Student.students.indexOf(new Student(Integer.parseInt(scode.getText().toString()), -1, null, null, null));
            if (ind < 0) {
                root.findViewById(R.id._404).setVisibility(View.VISIBLE);
            } else {
                scode.setVisibility(View.INVISIBLE);
                search.setVisibility(View.INVISIBLE);
                root.findViewById(R.id.editor).setVisibility(View.VISIBLE);

                Student edit = Student.students.get(ind);

                Spinner dcode = root.findViewById(R.id.dcode);
                ArrayAdapter<String> adapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_spinner_item, DCODES);
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
                dcode.setAdapter(adapter);
                dcode.setSelection(edit.getDcode() - 1);
                TextView name = root.findViewById(R.id.name);
                name.setText(edit.getName());
                TextView address = root.findViewById(R.id.address);
                address.setText(edit.getAddress());
                TextView phone = root.findViewById(R.id.phone);
                phone.setText(edit.getPhone());

                Button submit = root.findViewById(R.id.submit);
                submit.setOnClickListener(v2 -> {
                    if (name.getText().toString().equals("") || address.getText().toString().equals("") || phone.getText().toString().equals("")) {
                        new AlertDialog.Builder(getActivity())
                                .setTitle("Invalid input(s)")
                                .setNeutralButton("OK", null)
                                .show();
                        return;
                    }

                    edit.setDcode(dcode.getSelectedItemPosition() + 1);
                    edit.setName(name.getText().toString());
                    edit.setAddress(address.getText().toString());
                    edit.setPhone(phone.getText().toString());

                    getFragmentManager().popBackStack();
                });

                Button cancel = root.findViewById(R.id.cancel);
                cancel.setOnClickListener(v2 -> {
                    getFragmentManager().popBackStack();
                });
            }
        });

        return root;
    }
}