package com.rgdgr8.dbms02;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

public class DisplayFragment extends Fragment {
    private int numOfPages;
    private int remainder;
    private int pageNo = 0; //0 indexed
    private Button next;
    private Button prev;
    private final TextView[] records = new TextView[5];

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        /*
        for (int i = 0; i < 4; i++) {
            Student.students.add(new Student(i + 1, 1, "", "", ""));
        }
        /*Demo data*/

        View root = inflater.inflate(R.layout.fragment_display, container, false);
        numOfPages = Student.students.size() / 5;
        remainder = Student.students.size() % 5;
        if (remainder == 0) {
            numOfPages--;
            remainder = 5;
        }

        TextView r1 = root.findViewById(R.id.r1);
        TextView r2 = root.findViewById(R.id.r2);
        TextView r3 = root.findViewById(R.id.r3);
        TextView r4 = root.findViewById(R.id.r4);
        TextView r5 = root.findViewById(R.id.r5);
        records[0] = r1;
        records[1] = r2;
        records[2] = r3;
        records[3] = r4;
        records[4] = r5;

        next = root.findViewById(R.id.next);
        next.setOnClickListener(v -> {
            for (TextView record : records) {
                record.setText("");
            }

            pageNo++;

            prev.setVisibility(View.VISIBLE);
            int st = pageNo * 5;
            int en = st + 5;
            if (pageNo == numOfPages) {
                next.setVisibility(View.INVISIBLE);
                en = st + remainder;
            }

            int j = 0;
            for (int i = st; i < en; i++) {
                records[j++].setText(Student.students.get(i).toString());
            }
        });

        prev = root.findViewById(R.id.prev);
        prev.setOnClickListener(v -> {
            for (TextView record : records) {
                record.setText("");
            }

            pageNo--;

            next.setVisibility(View.VISIBLE);
            int st = pageNo * 5;
            int en = st + 5;

            if (pageNo == 0) {
                prev.setVisibility(View.INVISIBLE);
            }

            int j = 0;
            for (int i = st; i < en; i++) {
                records[j++].setText(Student.students.get(i).toString());
            }
        });
        prev.setVisibility(View.INVISIBLE);

        if (Student.students.size() < 6) {
            next.setVisibility(View.INVISIBLE);
        }

        if (Student.students.size() < 1)
            r1.setText("No records present");
        else {
            int run = Math.min(Student.students.size(), 5);
            Log.d("run,size", run + "," + Student.students.size());
            for (int i = 0; i < run; i++) {
                records[i].setText(Student.students.get(i).toString());
            }
        }

        return root;
    }
}