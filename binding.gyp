{
    "targets": [
        {
            "target_name": "gss",
            "sources": [
                "src/gss.cc",
                "src/name.cc",
                "src/util.cc",
            ],
            "link_settings": {
                "libraries": [
                    "-lgssapi_krb5"
                ]
            },
            "cflags": [
                "-W", "-Wall", "-Wno-unused-parameter"
            ]
        }
    ]
}
