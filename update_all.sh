#!/bin/bash -       
git add *
echo "Commit message: "
read COMMITMESSAGE
git commit -m "$COMMITMESSAGE"
git push origin master