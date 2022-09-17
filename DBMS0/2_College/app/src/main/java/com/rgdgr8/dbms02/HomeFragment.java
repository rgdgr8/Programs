package com.rgdgr8.dbms02;

import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

public class HomeFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View root = inflater.inflate(R.layout.fragment_home, container, false);

        Button add = root.findViewById(R.id.add);
        add.setOnClickListener(new DbButtonClick("add"));
        Button search = root.findViewById(R.id.search);
        search.setOnClickListener(new DbButtonClick("search"));
        Button edit = root.findViewById(R.id.edit);
        edit.setOnClickListener(new DbButtonClick("edit"));
        Button delete = root.findViewById(R.id.delete);
        delete.setOnClickListener(new DbButtonClick("delete"));
        Button display = root.findViewById(R.id.display);
        display.setOnClickListener(new DbButtonClick("display"));

        return root;
    }

    class DbButtonClick implements View.OnClickListener {
        private String fragName;
        DbButtonClick(String name){fragName = name;}

        @Override
        public void onClick(View v) {
            FragmentTransaction transaction = getFragmentManager().beginTransaction();

            switch (fragName){
                case "add": transaction.replace(R.id.frame, new AddFragment(), fragName.toUpperCase());break;
                case "search": transaction.replace(R.id.frame, new SearchFragment(), fragName.toUpperCase());break;
                case "edit": transaction.replace(R.id.frame, new EditFragment(), fragName.toUpperCase());break;
                case "delete": transaction.replace(R.id.frame, new DeleteFragment(), fragName.toUpperCase());break;
                case "display": transaction.replace(R.id.frame, new DisplayFragment(), fragName.toUpperCase()); break;
                default: return;
            }

            transaction.addToBackStack(null);
            transaction.commit();
        }
    }
}