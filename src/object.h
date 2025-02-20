#pragma once
#include <raylib.h>

class P1{
    public:
        P1();
        ~P1();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;
        
        private:
            Texture2D p1;
            Texture2D up;
            Texture2D down;
            Texture2D left;
            Texture2D right;

            float scale;
};

class P2{
    public:
        P2();
        ~P2();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;

    private:
        Texture2D p2;
        Texture2D up;
        Texture2D down;
        Texture2D left;
        Texture2D right;

        float scale;
};

class oppositecommand{
    public:
        oppositecommand();
        ~oppositecommand();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;

    private:
        Texture2D up;
        Texture2D down;
        Texture2D left;
        Texture2D right;

        float scale;
};

class command{
    public:
        command();
        ~command();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;

    private:
        Texture2D up;
        Texture2D down;
        Texture2D left;
        Texture2D right;

        float scale;
};

class Commander{
    public:
        Commander();
        ~Commander();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;

    private:
        Texture2D C1;
        Texture2D C2;
        Texture2D C1attack;
        Texture2D C2attack;

        float scale;
};

class check{
    public:
        check();
        ~check();
        void load();
        void unload();
        void draw(Vector2 position,int direction) const;
        void setscale(float scale);
        Vector2 position;
        int direction;

    private:
        Texture2D correct;
        Texture2D incorrect;
        Texture2D blank;

        float scale;
};

class result{
    public:
        result();
        ~result();
        void load();
        void unload();
        void draw(int direction) const;

    private:
        Texture2D P1win;
        Texture2D P2win;
        Texture2D Draw;
};