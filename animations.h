#ifndef ANIMATIONS_H
#define ANIMATIONS_H

int GetStatus();
void SetStatus(int val);
int GetMode();

void ChangeAnimation(uint mode);
void ChangePrevAnimation();
void ChangeNextAnimation();

void AnimationUpdate();

#endif