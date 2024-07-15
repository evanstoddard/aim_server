CREATE TABLE users(
    uin TEXT NOT NULL,
    email TEXT NOT NULL,
    hashed_password TEXT NOT NULL
);

CREATE TABLE challenge_keys(
    uin TEXT NOT NULL
    text TEXT NOT NULL
    FOREIGN KEY(uin) REFERENCES users(uin)
);